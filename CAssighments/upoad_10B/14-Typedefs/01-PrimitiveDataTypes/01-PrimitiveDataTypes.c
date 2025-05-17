#include<stdio.h>

//global typedef
typedef int MY_INT;	// existing datatypes with new name redefine the name of already existng data 

int main(void)
{
	MY_INT add(MY_INT, MY_INT);

	//typedfes
	typedef int MY_INT;
	typedef float PVG_FLOAT;
	typedef char CHARACTER;
	typedef double MY_DOUBLE;

	typedef unsigned int UINT;
	typedef UINT HANDLE;
	typedef HANDLE HWND;
	typedef HANDLE HINSTANCE;

	MY_INT a = 10;

	MY_INT Array_int[] = {12, 24, 36, 48, 60, 72, 84, 96, 108, 120};

	PVG_FLOAT f_pvg = 12.45f;
	const PVG_FLOAT f_pvg_pi = 3.14f;

	CHARACTER ch = '*';
	CHARACTER Array_Ch1[] = "Hello";
	CHARACTER Array_ch2[][10] = { "My","Name","Is", "Rajashree" };

	MY_DOUBLE d = 8.7887;


	UINT unit = 6787;
	HANDLE handle = 87567;
	HWND hwnd = 7687;
	HINSTANCE hInstance = 13234;

	printf("\n\n");
	printf("Type My_int variable a = %d\n\n", a);

	for (int i = 0; i < (sizeof(Array_int) / sizeof(Array_int[0])); i++) {
		printf("Type MY_INT Array_int[%d] = %d\n", i, Array_int[i]);
	}

	printf("Type of PVG_FLOAT f_pvg = %f\n\n", f_pvg);

	printf("Type of PVG_FLOAT f_pvg_pi = %f\n\n", f_pvg_pi);

	printf("Type of CHARACTER ch = %c\n\n", ch);

	printf("Type of CHARACTER Array_Ch1[0] = %s\n\n", Array_Ch1);
	//printf("Type of CHARACTER Array_Ch2[][10] = %s\n\n", Array_Ch2);

	for (int i = 0; i < (sizeof(Array_ch2) / sizeof(Array_ch2[0])); i++) {
		printf("%s\t", Array_ch2[i]);
	}

	printf("\n\n");
	printf("type of Double d=%lf\n\n", d);

	printf("type of UNIT unit =%u\n", unit);
	printf("type of HANDLE handle d=%u\n", unit);
	printf("type of HWND hwnd d=%u\n", hwnd);
	printf("type of HINSTANCE hInstance d=%u\n\n", hInstance);

	MY_INT x = 677;
	MY_INT y = 677;

	MY_INT result;
	result = add(x, y);
	printf("result =%d\n\n", result);

	return 0;
}

int add(MY_INT a, MY_INT b)
{
	MY_INT c;
	c = a + b;
	return(c);
}