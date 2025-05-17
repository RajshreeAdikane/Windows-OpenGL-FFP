#include<stdio.h>

int main(void)
{
	int iArray[] = { 2,4,6,8,10,12,14,16,18,20 };
	int* ptr = NULL;

	printf("\n\n");
	printf("Array elements and Address\n");
	printf("iArray[0] = %d \t Address:%p\n", iArray[0], (iArray + 0));
	printf("iArray[1] = %d \t Address:%p\n", iArray[1], (iArray + 1));
	printf("iArray[2] = %d \t Address:%p\n", iArray[2], (iArray + 2));
	printf("iArray[3] = %d \t Address:%p\n", iArray[3], (iArray + 3));
	printf("iArray[4] = %d \t Address:%p\n", iArray[4], (iArray + 4));
	printf("iArray[5] = %d \t Address:%p\n", iArray[5], (iArray + 5));
	printf("iArray[6] = %d \t Address:%p\n", iArray[6], (iArray + 6));
	printf("iArray[7] = %d \t Address:%p\n", iArray[7], (iArray + 7));
	printf("iArray[8] = %d \t Address:%p\n", iArray[8], (iArray + 8));
	printf("iArray[9] = %d \t Address:%p\n", iArray[9], (iArray + 9));

	ptr = iArray;
	printf("\n\n");
	printf("Using Pointers: Array elements and Address\n");
	printf("ptr[0] = %d \t Address:%p\n", *(ptr + 0), (ptr + 0));
	printf("ptr[1] = %d \t Address:%p\n", *(ptr + 1), (ptr + 1));
	printf("ptr[2] = %d \t Address:%p\n", *(ptr + 2), (ptr + 2));
	printf("ptr[3] = %d \t Address:%p\n", *(ptr + 3), (ptr + 3));
	printf("ptr[4] = %d \t Address:%p\n", *(ptr + 4), (ptr + 4));
	printf("ptr[5] = %d \t Address:%p\n", *(ptr + 5), (ptr + 5));
	printf("ptr[6] = %d \t Address:%p\n", *(ptr + 6), (ptr + 6));
	printf("ptr[7] = %d \t Address:%p\n", *(ptr + 7), (ptr + 7));
	printf("ptr[8] = %d \t Address:%p\n", *(ptr + 8), (ptr + 8));
	printf("ptr[9] = %d \t Address:%p\n", *(ptr + 9), (ptr + 9));


	return 0;
}
