#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define ARRAY_SIZE 5

const char* kernelSource =
"__kernel void vecAddGPU(__global float* in1, __global float* in2, __global float* out, __global int* deviceIndex, const int len) {\n"
"    int i = get_global_id(0);\n"
"    if (i < len) {\n"
"        deviceIndex[i] = 5;\n"
"        out[i] = in1[i] + in2[i];\n"
"    }\n"
"}\n";

int main(void) {
    float* hostInput1, * hostInput2, * hostOutput;
    int* hostIndex;
    cl_int err;

    size_t dataSize = ARRAY_SIZE * sizeof(float);
    size_t indexSize = ARRAY_SIZE * sizeof(int);

    // Allocate host memory
    hostInput1 = (float*)malloc(dataSize);
    hostInput2 = (float*)malloc(dataSize);
    hostOutput = (float*)malloc(dataSize);
    hostIndex = (int*)malloc(indexSize);

    // Fill input arrays
    hostInput1[0] = 101.0f; hostInput1[1] = 102.0f; hostInput1[2] = 103.0f; hostInput1[3] = 104.0f; hostInput1[4] = 105.0f;
    hostInput2[0] = 201.0f; hostInput2[1] = 202.0f; hostInput2[2] = 203.0f; hostInput2[3] = 204.0f; hostInput2[4] = 205.0f;

    // OpenCL setup
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;

    err = clGetPlatformIDs(1, &platform, NULL);
    err |= clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    queue = clCreateCommandQueueWithProperties(context, device, 0, &err);

    // Create memory buffers on device
    cl_mem deviceInput1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, dataSize, hostInput1, &err);
    cl_mem deviceInput2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, dataSize, hostInput2, &err);
    cl_mem deviceOutput = clCreateBuffer(context, CL_MEM_WRITE_ONLY, dataSize, NULL, &err);
    cl_mem deviceIndex = clCreateBuffer(context, CL_MEM_WRITE_ONLY, indexSize, NULL, &err);

    // Create and build the program
    program = clCreateProgramWithSource(context, 1, &kernelSource, NULL, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    // Create kernel
    kernel = clCreateKernel(program, "vecAddGPU", &err);

    // Set kernel arguments
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &deviceInput1);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &deviceInput2);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &deviceOutput);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &deviceIndex);
    clSetKernelArg(kernel, 4, sizeof(int), &ARRAY_SIZE);

    // Execute kernel
    size_t globalWorkSize = ARRAY_SIZE;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalWorkSize, NULL, 0, NULL, NULL);

    // Read result back to host
    clEnqueueReadBuffer(queue, deviceOutput, CL_TRUE, 0, dataSize, hostOutput, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, deviceIndex, CL_TRUE, 0, indexSize, hostIndex, 0, NULL, NULL);

    // Print results
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%f + %f = %f , %d\n", hostInput1[i], hostInput2[i], hostOutput[i], hostIndex[i]);
    }

    // Cleanup
    clReleaseMemObject(deviceInput1);
    clReleaseMemObject(deviceInput2);
    clReleaseMemObject(deviceOutput);
    clReleaseMemObject(deviceIndex);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    free(hostInput1);
    free(hostInput2);
    free(hostOutput);
    free(hostIndex);

    return 0;
}
