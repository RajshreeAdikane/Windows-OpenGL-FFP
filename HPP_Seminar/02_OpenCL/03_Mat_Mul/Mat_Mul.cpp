#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <time.h>

#define BLOCK_WIDTH 32

int* hostA, * hostB, * hostC, * gold;

float timeOnCPU = 0.0f;
float timeOnGPU = 0.0f;

void initA(int* data, int row, int col);
void initB(int* data, int row, int col);
void matMulCPU(int* A, int* B, int* C, int numARows, int numAColumns, int numBColumns, int numCColumns);

const char* kernelSource =
"__kernel void matMulGPU(__global int* A, __global int* B, __global int* C, int numARows, int numAColumns, int numBColumns, int numCColumns) {\n"
"    int row = get_global_id(1);\n"
"    int column = get_global_id(0);\n"
"    if(row < numARows && column < numBColumns) {\n"
"        int value = 0;\n"
"        for(int k = 0; k < numAColumns; ++k) {\n"
"            int a = A[row * numAColumns + k];\n"
"            int b = B[k * numBColumns + column];\n"
"            value += a * b;\n"
"        }\n"
"        C[row * numCColumns + column] = value;\n"
"    }\n"
"}\n";

int main() {
    int numARows = BLOCK_WIDTH;
    int numAColumns = BLOCK_WIDTH;
    int numBRows = BLOCK_WIDTH;
    int numBColumns = BLOCK_WIDTH;
    int numCRows = BLOCK_WIDTH;
    int numCColumns = BLOCK_WIDTH;

    size_t sizeA = numARows * numAColumns * sizeof(int);
    size_t sizeB = numBRows * numBColumns * sizeof(int);
    size_t sizeC = numCRows * numCColumns * sizeof(int);

    hostA = (int*)malloc(sizeA);
    hostB = (int*)malloc(sizeB);
    hostC = (int*)malloc(sizeC);
    gold = (int*)malloc(sizeC);

    initA(hostA, numARows, numAColumns);
    initB(hostB, numBRows, numBColumns);

    cl_int err;
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;

    cl_mem d_A, d_B, d_C;

    err = clGetPlatformIDs(1, &platform, NULL);
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    queue = clCreateCommandQueue(context, device, 0, &err);

    d_A = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeA, NULL, &err);
    d_B = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeB, NULL, &err);
    d_C = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeC, NULL, &err);

    clEnqueueWriteBuffer(queue, d_A, CL_TRUE, 0, sizeA, hostA, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, d_B, CL_TRUE, 0, sizeB, hostB, 0, NULL, NULL);

    program = clCreateProgramWithSource(context, 1, &kernelSource, NULL, &err);
    clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    kernel = clCreateKernel(program, "matMulGPU", &err);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_A);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_B);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_C);
    clSetKernelArg(kernel, 3, sizeof(int), &numARows);
    clSetKernelArg(kernel, 4, sizeof(int), &numAColumns);
    clSetKernelArg(kernel, 5, sizeof(int), &numBColumns);
    clSetKernelArg(kernel, 6, sizeof(int), &numCColumns);

    size_t globalSize[2] = { numBColumns, numARows };
    size_t localSize[2] = { BLOCK_WIDTH, BLOCK_WIDTH };

    clock_t start_gpu = clock();
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, globalSize, localSize, 0, NULL, NULL);
    clFinish(queue);
    clock_t end_gpu = clock();
    timeOnGPU = (float)(end_gpu - start_gpu) / CLOCKS_PER_SEC * 1000;

    clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, sizeC, hostC, 0, NULL, NULL);

    clock_t start_cpu = clock();
    matMulCPU(hostA, hostB, gold, numARows, numAColumns, numBColumns, numCColumns);
    clock_t end_cpu = clock();
    timeOnCPU = (float)(end_cpu - start_cpu) / CLOCKS_PER_SEC * 1000;

    int match = 1;
    for (int i = 0; i < numCRows * numCColumns; ++i) {
        if (hostC[i] != gold[i]) {
            printf("Mismatch at index %d: GPU %d, CPU %d\n", i, hostC[i], gold[i]);
            match = 0;
            break;
        }
    }

    printf("Matrix multiplication is %s\n", match ? "correct" : "incorrect");
    printf("Time on CPU: %.2f ms\n", timeOnCPU);
    printf("Time on GPU: %.2f ms\n", timeOnGPU);

    clReleaseMemObject(d_A);
    clReleaseMemObject(d_B);
    clReleaseMemObject(d_C);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    free(hostA);
    free(hostB);
    free(hostC);
    free(gold);

    return 0;
}

void initA(int* data, int row, int col) {
    int num = 1;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            data[i * col + j] = num++;
}

void initB(int* data, int row, int col) {
    int num = BLOCK_WIDTH;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            data[i * col + j] = num--;
}

void matMulCPU(int* A, int* B, int* C, int numARows, int numAColumns, int numBColumns, int numCColumns) {
    for (int i = 0; i < numARows; ++i)
        for (int j = 0; j < numBColumns; ++j) {
            int value = 0;
            for (int k = 0; k < numAColumns; ++k)
                value += A[i * numAColumns + k] * B[k * numBColumns + j];
            C[i * numCColumns + j] = value;
        }
}
