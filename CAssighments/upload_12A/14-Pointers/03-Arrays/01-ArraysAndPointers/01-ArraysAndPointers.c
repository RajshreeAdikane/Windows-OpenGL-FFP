#include<stdio.h>

int main(void)
{
	int iArray[] = { 2,4,6,8,10,12,14,16,18,20 };
	float fArray[] = { 1.2f,3.4f,6.7f,8.9f };
	double dArray[] = { 1.222222,3.555555555,7.458765 };
	char cArray[] = { 'R','A','J','S','H','R','E','E','\0' };

	printf("\n\n");
	printf("Inter array elements and Address\n");
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

	printf("\n\n");
	printf("Float array elements and Address\n");
	printf("fArray[0] = %f \t Address:%p\n", fArray[0], (fArray + 0));
	printf("fArray[1] = %f \t Address:%p\n", fArray[1], (fArray + 1));
	printf("fArray[2] = %f \t Address:%p\n", fArray[2], (fArray + 2));
	printf("fArray[3] = %f \t Address:%p\n", fArray[3], (fArray + 3));

	printf("\n\n");
	printf("Double array elements and Address\n");
	printf("dArray[0] = %lf \t Address:%p\n", dArray[0], (dArray + 0));
	printf("dArray[1] = %lf \t Address:%p\n", dArray[1], (dArray + 1));
	printf("dArray[2] = %lf \t Address:%p\n", dArray[2], (dArray + 2));

	printf("\n\n");
	printf("Character array elements and Address\n");
	printf("cArray[0] = %c \t Address:%p\n", cArray[0], (cArray + 0));
	printf("cArray[1] = %c \t Address:%p\n", cArray[1], (cArray + 1));
	printf("cArray[2] = %c \t Address:%p\n", cArray[2], (cArray + 2));
	printf("cArray[3] = %c \t Address:%p\n", cArray[3], (cArray + 3));
	printf("cArray[4] = %c \t Address:%p\n", cArray[4], (cArray + 4));
	printf("cArray[5] = %c \t Address:%p\n", cArray[5], (cArray + 5));
	printf("cArray[6] = %c \t Address:%p\n", cArray[6], (cArray + 6));
	printf("cArray[7] = %c \t Address:%p\n", cArray[7], (cArray + 7));

	return 0;
}
