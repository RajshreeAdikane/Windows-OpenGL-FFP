#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>

void PrintOpenCLDeviceProperties();

int main(void)
{
    PrintOpenCLDeviceProperties();
    return 0;
}

void PrintOpenCLDeviceProperties()
{
    cl_platform_id *platforms = NULL;
    cl_device_id *devices = NULL;
    cl_uint num_platforms = 0;
    cl_uint num_devices = 0;
    cl_int ret;

    // Get number of platforms
    ret = clGetPlatformIDs(0, NULL, &num_platforms);
    if (ret != CL_SUCCESS || num_platforms == 0)
    {
        printf("Failed to find any OpenCL platforms.\n");
        return;
    }

    platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * num_platforms);
    ret = clGetPlatformIDs(num_platforms, platforms, NULL);

    printf("OpenCL INFORMATION:\n");
    printf("===============================\n");
    printf("Total Number of OpenCL Platforms: %u\n\n", num_platforms);

    for (cl_uint i = 0; i < num_platforms; i++)
    {
        char platform_name[128];
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(platform_name), platform_name, NULL);
        printf("Platform %u: %s\n", i, platform_name);

        // Get devices for this platform
        ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
        if (ret != CL_SUCCESS || num_devices == 0)
        {
            printf("  No OpenCL devices found on this platform.\n\n");
            continue;
        }

        devices = (cl_device_id *)malloc(sizeof(cl_device_id) * num_devices);
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);

        printf("  Total Devices: %u\n", num_devices);

        for (cl_uint j = 0; j < num_devices; j++)
        {
            char device_name[128];
            char device_vendor[128];
            char driver_version[128];
            cl_uint compute_units;
            cl_uint clock_frequency;
            cl_uint max_work_group_size;
            char device_version[128];

            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(device_name), device_name, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, sizeof(device_vendor), device_vendor, NULL);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, sizeof(driver_version), driver_version, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, sizeof(device_version), device_version, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(compute_units), &compute_units, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(clock_frequency), &clock_frequency, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);

            printf("  ---------------------------------------------\n");
            printf("  Device %u:\n", j);
            printf("    Name                : %s\n", device_name);
            printf("    Vendor              : %s\n", device_vendor);
            printf("    Driver Version      : %s\n", driver_version);
            printf("    OpenCL Version      : %s\n", device_version);
            printf("    Compute Units       : %u\n", compute_units);
            printf("    Max Clock Frequency : %u MHz\n", clock_frequency);
            printf("    Max Work Group Size : %u\n", max_work_group_size);
            printf("  ---------------------------------------------\n\n");
        }

        free(devices);
    }

    free(platforms);
}
