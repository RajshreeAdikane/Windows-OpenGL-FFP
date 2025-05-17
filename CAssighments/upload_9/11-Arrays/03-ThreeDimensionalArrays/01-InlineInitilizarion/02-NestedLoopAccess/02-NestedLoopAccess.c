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

	for (int i = 0; i < Array3D_width; i++)
	{
		printf("***********ROW%d************\n", (i + 1));
		for (int j = 0; j < Array3D_height; j++)
		{
			printf("***********COLOUM%d************\n", (j + 1));
			for (int k = 0; k < Array3D_depth; k++)
			{
				printf("Array 3D [%d][%d][%d] = %d\n", i, j, k, Array3D[i][j][k]);
			}
		}
		    printf("\n\n");

	}

	return 0;

}