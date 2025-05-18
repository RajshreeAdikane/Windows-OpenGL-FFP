#include <stdio.h>
#include <cuda.h>

int main(void)
{
    // function declarations
    void PrintCUDADeviceProperties(void);

    // code
    PrintCUDADeviceProperties();

    return (0);
}

int GetNumberOfCores(cudaDeviceProp devProp)
{
    int cores = 0;
    int mp = devProp.multiProcessorCount;

    switch (devProp.major)
    {
    case 1:  // Tesla architecture (compute capability 1.x)
        cores = mp * 8;
        break;
    case 2:  // Fermi architecture (compute capability 2.x)
        cores = mp * 32;
        break;
    case 3:  // Kepler architecture (compute capability 3.x)
        cores = mp * 192;
        break;
    case 5:  // Maxwell architecture (compute capability 5.x)
        cores = mp * 128;
        break;
    case 6:  // Pascal architecture (compute capability 6.x)
        if (devProp.minor == 1 || devProp.minor == 2)
            cores = mp * 128;  // GP100, GP102
        else
            cores = mp * 64;   // GP104, GP106, GP107, etc.
        break;
    case 7:  // Volta architecture (compute capability 7.x)
        cores = mp * 64;
        break;
    case 8:  // Ampere architecture (compute capability 8.x)
        cores = mp * 128;
        break;
    case 9:  // Hopper architecture (compute capability 9.x)
        cores = mp * 128;
        break;
    default:
        printf("Unknown GPU architecture. Cannot determine number of cores.\n");
        break;
    }

    return cores;
}

void PrintCUDADeviceProperties(void)
{
    // code
    printf("CUDA INFORMATION : \n");
    printf("=============================== \n");

    cudaError_t ret_cuda_rt;
    int dev_count;
    ret_cuda_rt = cudaGetDeviceCount(&dev_count);
    if (ret_cuda_rt != cudaSuccess)
    {
        printf("CUDA Runtime API Error - cudaGetDeviceCount() Failed Due To %s. ? \n", cudaGetErrorString(ret_cuda_rt));
    }
    else if (dev_count == 0)
    {
        printf("There Is No CUDA Supported Device On This System.\n");
        return;
    }
    else
    {
        printf("Total Number Of CUDA Supporting GPU Device/Devices On This System : %d\n", dev_count);
        for (int i = 0; i < dev_count; i++)
        {
            cudaDeviceProp dev_prop;
            memset((void *)&dev_prop, 0, sizeof(cudaDeviceProp));
            int driverVersion = 0, runtimeVersion = 0;

            ret_cuda_rt = cudaGetDeviceProperties(&dev_prop, i);
            if (ret_cuda_rt != cudaSuccess)
            {
                printf("%s in %s at line %d\n", cudaGetErrorString(ret_cuda_rt), __FILE__, __LINE__);
                return;
            }
            printf("\n");
            cudaDriverGetVersion(&driverVersion);
            cudaRuntimeGetVersion(&runtimeVersion);
            printf("******* CUDA DRIVER AND RUNTIME INFORMATION *******\n");
            printf("=============================== \n");
            printf("CUDA Driver Version : %d.%d\n", driverVersion / 1000, (driverVersion % 100) / 10);
            printf("CUDA Runtime Version : %d.%d\n", runtimeVersion / 1000, (runtimeVersion % 100) / 10);
            printf("CUDA Compute Capability Major = %d and Minor = %d\n", dev_prop.major, dev_prop.minor);
            printf("CUDA Cores: %d\n", GetNumberOfCores(dev_prop));
            
#if defined(MIN32) || defined(_MIN32) || defined(MING4) || defined(_MIN64)
            printf("GPU Device CUDA Driver Mode ( TCC Or WDDM )    : %s\n", dev_prop.tccDriver ? "TCC ( Tesla Compute Cluster Driver )" : "WDDM ( Windows Display Driver Model )");
#endif
            printf("**********************************************************************\n");
        }
    }
}
