#include <stdio.h>
#include <cuda.h>

#include "helper_timer.h"

const int iNumberOfArrayElement = 114447777;

float* hostInput1 = NULL;
float* hostInput2 = NULL;
float* hostOutput = NULL;
float* gold = NULL;

float* deviceInput1 = NULL;
float* deviceInput2 = NULL;
float* deviceOutput = NULL;

float timerOnCPU = 0.0f;
float timerOnGPU = 0.0f;

__global__ void vecAddGPU(float* in1, float* in2, float* out,int len)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if(i < len)
    {
        out[i] = in1[i] + in2[i];
    }
}
int main(void)
{
    void cleanup(void);
    void vecAddCPU(float* arr1, float* arr2, float* out,int len);
    void FillFloatArrayWithRandomNumber(float*, int);

    cudaError_t result = cudaSuccess;
    int size = iNumberOfArrayElement * sizeof(float);
    hostInput1 = (float *)malloc(size);
    if(hostInput1 == NULL)
    {
        printf("Host memory allocation failed for hostInput1 array\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    hostInput2 = (float *)malloc(size);
    if(hostInput2 == NULL)
    {
        printf("Host memory allocation failed for hostInput2 array\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    hostOutput = (float *)malloc(size);
    if(hostOutput == NULL)
    {
        printf("Host memory allocation failed for hostOutput array\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    gold = (float *)malloc(size);
    if(gold == NULL)
    {
        printf("Host memory allocation failed for gold array\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    FillFloatArrayWithRandomNumber(hostInput1, iNumberOfArrayElement);
    FillFloatArrayWithRandomNumber(hostInput2, iNumberOfArrayElement);


    result = cudaMalloc((void**)&deviceInput1, size);
    if(result != cudaSuccess)
    {
        printf("Device memory allocation failed for deviceInput1 array : reason = %s, File = %s, LineNo = %d\n", cudaGetErrorString(result), __FILE__, __LINE__);
        cleanup();
        exit(EXIT_FAILURE);
    }

    result = cudaMalloc((void**)&deviceInput2, size);
    if(result != cudaSuccess)
    {
        printf("Device memory allocation failed for deviceInput2 array : reason = %s, File = %s, LineNo = %d\n", cudaGetErrorString(result), __FILE__, __LINE__);
        cleanup();
        exit(EXIT_FAILURE);
    }

    result = cudaMalloc((void**)&deviceOutput, size);
    if(result != cudaSuccess)
    {
        printf("Device memory allocation failed for deviceOutput array : reason = %s, File = %s, LineNo = %d\n", cudaGetErrorString(result), __FILE__, __LINE__);
        cleanup();
        exit(EXIT_FAILURE);
    }

    result = cudaMemcpy((void *)deviceInput1, (void *)hostInput1, size, cudaMemcpyHostToDevice);
    if(result != cudaSuccess)
    {
        printf("Host to Device Copy Failed for deviceInput1\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    result = cudaMemcpy((void *)deviceInput2, (void *)hostInput2, size, cudaMemcpyHostToDevice);
    if(result != cudaSuccess)
    {
        printf("Host to Device Copy Failed for deviceInput2\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    dim3 dimGrid = dim3((int)ceil((float)iNumberOfArrayElement / 256.0f), 1, 1);
    dim3 dimBlock = dim3(1, 1, 1);

    StopWatchInterface *timer = NULL;
    sdkCreateTimer(&timer);
    sdkStartTimer(&timer);

    vecAddGPU <<<dimGrid, dimBlock>>>(deviceInput1, deviceInput2, deviceOutput, iNumberOfArrayElement);

    result = cudaGetLastError();
    if (result != cudaSuccess)
    {
        printf("Kernel launch failed: %s\n", cudaGetErrorString(result));
        cleanup();
        exit(EXIT_FAILURE);
    }

    sdkStopTimer(&timer);
    timerOnGPU = sdkGetTimerValue(&timer);
    sdkDeleteTimer(&timer);
    timer = NULL;

    result = cudaMemcpy((void *)hostOutput, (void *)deviceOutput, size, cudaMemcpyDeviceToHost);
    if(result != cudaSuccess)
    {
        printf("Device to Host copt data failed for hostOutput array\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    vecAddCPU(hostInput1, hostInput2, gold, iNumberOfArrayElement);

    //checking accurecy of the data
    const float epsilon = 0.000001f;
    bool bAccurecy = TRUE;
    int breakValue = -1;

    for(int i = 0; i < iNumberOfArrayElement; ++i)
    {
        float val1 = gold[i];
        float val2 = hostOutput[i];
        if(fabs(val1 - val2) > epsilon)
        {
            bAccurecy = FALSE;
            breakValue = i;
            break;
        }
    }
    
    if(bAccurecy == FALSE)
    {
        printf("Not Accurate iteration = %d\n", breakValue);
    }
    else
    {
        printf("Accurate\n");
    }
    printf("Time Taken On CPU = %f\n", timerOnCPU);
    printf("Time Taken On GPU = %f\n", timerOnGPU);
    cleanup();
    return (0);
}

void cleanup(void)
{
    if(deviceOutput)
    {
        cudaFree(deviceOutput);
        deviceOutput = NULL;
    }
    if(deviceInput2)
    {
        cudaFree(deviceInput2);
        deviceInput2 = NULL;
    }
    if(deviceInput1)
    {
        cudaFree(deviceInput1);
        deviceInput1 = NULL;
    }

    if(gold)
    {
        free(gold);
        gold = NULL;
    }


    if(hostOutput)
    {
        free(hostOutput);
        hostOutput = NULL;
    }
    if(hostInput2)
    {
        free(hostInput2);
        hostInput2 = NULL;
    }
    if(hostInput1)
    {
        free(hostInput1);
        hostInput1 = NULL;
    }
}

void FillFloatArrayWithRandomNumber(float* pArray, int len)
{
    const float fscale = 1.0f / (float)RAND_MAX;
    for(int i = 0; i < len; ++i)
    {
        pArray[i] = fscale * rand();
    }
}

void vecAddCPU(float* arr1, float* arr2, float* out,int len)
{
    StopWatchInterface *timer = NULL;
    sdkCreateTimer(&timer);
    sdkStartTimer(&timer);

    for(int i = 0; i < len; ++i)
    {
        out[i] = arr1[i] + arr2[i];
    }

    sdkStopTimer(&timer);
    timerOnCPU = sdkGetTimerValue(&timer);
    sdkDeleteTimer(&timer);
    timer = NULL;    
}
