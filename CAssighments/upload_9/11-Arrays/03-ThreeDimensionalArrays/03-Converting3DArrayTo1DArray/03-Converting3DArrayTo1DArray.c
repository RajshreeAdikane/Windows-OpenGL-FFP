#include<stdio.h>

#define NUM_ROWS 5
#define	NUM_COL 3
#define	DEPTH 2

int main(void)
{
	int Array3D[NUM_ROWS][NUM_COL][DEPTH] = { {{5,10}, {15,20},{25,30}},
		{{35,40}, {45, 50}, {55, 60}},
		{{65,70}, {75,80},{85,90}},
		{{95, 100},{105,110},{115,120}},
		{{125,130},{135,140},{145,150}}
	};

	int Array1D[NUM_ROWS * NUM_COL * DEPTH];
	int int_size;
	int Array3D_size;
	int Array3D_num_ele, Array3D_width, Array3D_height, Array3D_depth;

	//code

	for (int i = 0; i < NUM_ROWS; i++)
	{
		printf("***********ROW%d************\n", (i + 1));
		for (int j = 0; j < NUM_COL; j++)
		{
			printf("***********COLOUM%d************\n", (j + 1));
			for (int k = 0; k < DEPTH; k++)
			{
				printf("Array 3D [%d][%d][%d] = %d\n", i, j, k, Array3D[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");

	}

	//converting 3D arry to 1d array
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COL; j++)
		{
			for (int k = 0; k < DEPTH; k++)
			{
				Array1D[(i * NUM_COL * DEPTH) + (j * DEPTH) + k] = Array3D[i][j][k];
			}
		}
		printf("\n\n");

	}

	//display
	printf("\n\n");
	printf("Elements in the 1D Array: \n\n");
	for (int i = 0; i < (NUM_ROWS * NUM_COL * DEPTH); i++)
	{
		printf("1D Array is [%d]\n", i, Array1D[i]);
	}

	return 0;

}