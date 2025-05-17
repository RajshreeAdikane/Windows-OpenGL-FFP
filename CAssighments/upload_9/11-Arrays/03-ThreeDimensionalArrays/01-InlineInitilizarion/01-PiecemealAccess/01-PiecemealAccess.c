#include<stdio.h>

int main(void)
{
	int Array3D[5][3][2] = { {{5,10}, {15,20},{25,30}},
		{{35,40}, {45, 50}, {55, 60}},
		{{65,70}, {75,80},{85,90}},
		{{95, 100},{105,110},{115,120}},
		{{125,130},{135,140},{145,150}}
	};

	int int_size;
	int Array3D_size;
	int Array3D_num_ele, Array3D_width, Array3D_height, Array3D_depth;

	//code

	printf("\n\n");
	Array3D_size = sizeof(Array3D);
	printf("Sie od 3D array is: %d\n", Array3D_size);

	Array3D_width = Array3D_size / sizeof(Array3D[0]);
	printf("Number of rows or width of 3D Array is:%d\n", Array3D_width);

	Array3D_height = sizeof(Array3D[0]) / sizeof(Array3D[0][0]);
	printf("Number of colums or Height of 3D Array is:%d\n", Array3D_width);

	Array3D_depth = sizeof(Array3D[0][0]) / sizeof(Array3D[0][0][0]);
	printf("Depth of 3D Array is:%d\n", Array3D_width);

	Array3D_num_ele = Array3D_width * Array3D_height * Array3D_depth;
	printf("Total Number of elements 3D Array are:%d\n", Array3D_width);

    printf("***********ROW1************\n");
    printf("***********COLUMN1************\n");
    printf("Array 3D [0][0][0] = 5\n");
    printf("Array 3D [0][0][1] = 10\n");
    printf("***********COLUMN2************\n");
    printf("Array 3D [0][1][0] = 15\n");
    printf("Array 3D [0][1][1] = 20\n");
    printf("***********COLUMN3************\n");
    printf("Array 3D [0][2][0] = 25\n");
    printf("Array 3D [0][2][1] = 30\n");

    printf("\n***********ROW2************\n");
    printf("***********COLUMN1************\n");
    printf("Array 3D [1][0][0] = 35\n");
    printf("Array 3D [1][0][1] = 40\n");
    printf("***********COLUMN2************\n");
    printf("Array 3D [1][1][0] = 45\n");
    printf("Array 3D [1][1][1] = 50\n");
    printf("***********COLUMN3************\n");
    printf("Array 3D [1][2][0] = 55\n");
    printf("Array 3D [1][2][1] = 60\n");

    printf("\n***********ROW3************\n");
    printf("***********COLUMN1************\n");
    printf("Array 3D [2][0][0] = 65\n");
    printf("Array 3D [2][0][1] = 70\n");
    printf("***********COLUMN2************\n");
    printf("Array 3D [2][1][0] = 75\n");
    printf("Array 3D [2][1][1] = 80\n");
    printf("***********COLUMN3************\n");
    printf("Array 3D [2][2][0] = 85\n");
    printf("Array 3D [2][2][1] = 90\n");

    printf("\n***********ROW4************\n");
    printf("***********COLUMN1************\n");
    printf("Array 3D [3][0][0] = 95\n");
    printf("Array 3D [3][0][1] = 100\n");
    printf("***********COLUMN2************\n");
    printf("Array 3D [3][1][0] = 105\n");
    printf("Array 3D [3][1][1] = 110\n");
    printf("***********COLUMN3************\n");
    printf("Array 3D [3][2][0] = 115\n");
    printf("Array 3D [3][2][1] = 120\n");

    printf("\n***********ROW5************\n");
    printf("***********COLUMN1************\n");
    printf("Array 3D [4][0][0] = 125\n");
    printf("Array 3D [4][0][1] = 130\n");
    printf("***********COLUMN2************\n");
    printf("Array 3D [4][1][0] = 135\n");
    printf("Array 3D [4][1][1] = 140\n");
    printf("***********COLUMN3************\n");
    printf("Array 3D [4][2][0] = 145\n");
    printf("Array 3D [4][2][1] = 150\n");

    return 0;
}