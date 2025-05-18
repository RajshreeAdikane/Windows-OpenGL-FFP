#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 114447777
#define MAX_SOURCE_SIZE (0x100000)

float timerOnCPU = 0.0f;
float timerOnGPU = 0.0f;

void FillFloatArrayWithRandomNumber(float* arr, int len) {
    const float fscale = 1.0f / (float)RAND_MAX;
    for (int i = 0; i < len; ++i)
        arr[i] = fscale * rand();
}

void vecAddCPU(float* arr1, float* arr2, float* out, int len) {
    clock_t start = clock();
    for (int i = 0; i < len; ++i)
        out[i] = arr1[i] + arr2[i];
    clock_t end = clock();
    timerOnCPU = ((float)(end - start) / CLOCKS_PER_SEC) * 1000.0f;
}

const char* kernelSource =
"__kernel void vecAdd(__global float* A, __global float* B, __global float* C, int n) {     \n"
"    int id = get_global_id(0);                                                            \n"
"    if (id < n)                                                                           \n"
"        C[id] = A[id] + B[id];                                                            \n"
"}                                                                                         \n";

int main() {
    float* hostInput1 = NULL, * hostInput2 = NULL, * hostOutput = NULL, * gold = NULL;

    size_t bytes = ARRAY_SIZE * sizeof(float);

    hostInput1 = (float*)malloc(bytes);
    hostInput2 = (float*)malloc(bytes);
    hostOutput = (float*)malloc(bytes);
    gold = (float*)malloc(bytes);

    if (!hostInput1 || !hostInput2 || !hostOutput || !gold) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    FillFloatArrayWithRandomNumber(hostInput1, ARRAY_SIZE);
    FillFloatArrayWithRandomNumber(hostInput2, ARRAY_SIZE);

    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue queue = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;

    cl_mem d_input1, d_input2, d_output;
    cl_int ret;

    // Get platform and device
    ret = clGetPlatformIDs(1, &platform_id, NULL);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);

    // Create context
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

    // Create command queue with profiling
    queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &ret);

    // Allocate device memory
    d_input1 = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, &ret);
    d_input2 = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, &ret);
    d_output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bytes, NULL, &ret);

    // Copy data to device
    clEnqueueWriteBuffer(queue, d_input1, CL_TRUE, 0, bytes, hostInput1, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, d_input2, CL_TRUE, 0, bytes, hostInput2, 0, NULL, NULL);

    // Create and build program
    program = clCreateProgramWithSource(context, 1, (const char**)&kernelSource, NULL, &ret);
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create kernel
    kernel = clCreateKernel(program, "vecAdd", &ret);

    // Set kernel arguments
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_input1);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_input2);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_output);
    clSetKernelArg(kernel, 3, sizeof(int), &ARRAY_SIZE);

    size_t globalSize = ARRAY_SIZE;
    size_t localSize = 256;

    // Run kernel and profile
    cl_event event;
    ret = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize, 0, NULL, &event);
    clFinish(queue);

    // Get timing
    cl_ulong time_start, time_end;
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
    timerOnGPU = (time_end - time_start) / 1000000.0;

    // Read back result
    clEnqueueReadBuffer(queue, d_output, CL_TRUE, 0, bytes, hostOutput, 0, NULL, NULL);

    // Run CPU version
    vecAddCPU(hostInput1, hostInput2, gold, ARRAY_SIZE);

    // Verify
    const float epsilon = 0.000001f;
    int isCorrect = 1;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (fabs(gold[i] - hostOutput[i]) > epsilon) {
            printf("Mismatch at index %d: CPU = %f, GPU = %f\n", i, gold[i], hostOutput[i]);
            isCorrect = 0;
            break;
        }
    }

    if (isCorrect)
        printf("Accurate\n");
    printf("Time Taken On CPU = %f ms\n", timerOnCPU);
    printf("Time Taken On GPU = %f ms\n", timerOnGPU);

    // Cleanup
    clReleaseMemObject(d_input1);
    clReleaseMemObject(d_input2);
    clReleaseMemObject(d_output);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    free(hostInput1);
    free(hostInput2);
    free(hostOutput);
    free(gold);

    return 0;
}
