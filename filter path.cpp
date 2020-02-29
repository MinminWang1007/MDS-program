
#include "pch.h"
#include <iostream>
#include "stdlib.h"
#define M 1024
#define N 512
#define n 18
using namespace std;
int Integer_power(int num);
int path[M*M][8] = { 0 };
int Initialization[4][4] = { 1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1 };
void soft(int array[N], int j);
int cmp(const void *a, const void *b);

// There are $12$ different elementary matrices of Type $\rm{III}$ for
//$4\times 4$ matrices over $\mathbb{F}_{2^n}$
int Elementary_type[12][3] = {
	0, 0, 1, 1, 0, 2, 2, 0, 3, 3, 1, 0,  4, 1, 2,  5, 1, 3,
	6, 2, 0, 7, 2, 1, 8, 2, 3, 9, 3, 0, 10, 3, 1, 11, 3, 2,
};

//If each submatrices is nonsingular, then Matrix_A is an MDS matrix.
int MDS(int Matrix_A[4][4][N]);

// alpha_1 and alpha_2 are belong to the finite ring.   alpha_3 = alpha_1 + alpha_2
void addoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);

// alpha_1 and alpha_2 are belong to the finite ring.   alpha_3 = alpha_1 * alpha_2
void multoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);

// Elementary_number  is one of the $12$ different elementary matrices of Type $\rm{III}$
//Matrix_A=Elementary_number（alpha） such as 
//Matrix_A=\overline{1}(alpha)=
// 1 alpha 0 0
// 0   1   0 0
// 0   0   1 0
// 0   0   0 1
void transformation(int Matrix_A[4][4][N], int alpha, int Elementary_number);

//Matrix_A,Matrix_B and Matrix_C are 4*4 matrix over the finite ring. 
//Matrix_C = Matrix_A + Matrix_B.
void matrixadd(int Matrix_A[4][4][N], int Matrix_B[4][4][N], int Matrix_C[4][4][N]);


//Matrix_A,Matrix_B and Matrix_C are 4*4 matrix over the finite ring. 
//Matrix_C = Matrix_A * Matrix_B.
void matrixmult(int Matrix_A[4][4][N], int Matrix_B[4][4][N], int Matrix_C[4][4][N]);


//Matrix = Elementary_number（alpha）* Matrix
void Linear_operation(int Elementary_number, int alpha, int Matrix[4][4]);


//Remove the paths which induce matrices that always contain $0$.
int Step1(int leng[8]);


//Remove the paths which induce matrices with singular submatrices.
int Step2(int leng[8]);

// Printf path
void Printfpath(int leng[8]);

int main()
{	
	int B[4][4] = { 0 };
	int tt = 0;
	for (int i1 = 0; i1 < 12; i1++)
	{
		for (int i2 = 0; i2 < 12; i2++)
		{		
			for (int i3 = 0; i3 < 12; i3++)
			{
				for (int i4 = 0; i4 < 12; i4++)
				{
					for (int i5 = 0; i5 < 12; i5++)
					{
						for (int i6 = 0; i6 < 12; i6++)
						{
							for (int i7 = 0; i7 < 12; i7++)
							{

								int leng[8] = { 8,i1, i2, i3, i4, i5, i6, i7 };

								int t1 = Step1(leng);

								if (t1 == 1)
								{
									for (int i = 0; i < 8; i++)
									{
										path[tt][i] = leng[i];
									}
									tt = tt + 1;

								}

							}
							
						}
					}
				}
				
			}
		}
	}
	cout << tt;
	for (int i = 0; i < tt; i++)
	{
		int a = Step2(path[i]);
		if (a == 1)
		{
			Printfpath(path[i]);

		}

	}

}
int Step1(int leng[8])
{
	int B[4][4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			B[i][j] = Initialization[i][j];
		}
	}
	Linear_operation(leng[1], 1, B);
	Linear_operation(leng[2], 1, B);
	Linear_operation(leng[3], 1, B);
	Linear_operation(leng[4], 1, B);
	Linear_operation(leng[5], 1, B);
	Linear_operation(leng[6], 1, B);
	int t = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (B[i][j] == 0)
			{
				t = t + 1;

			}
		}
	}
	if (t <= 1)
	{
		Linear_operation(leng[7], 1, B);
		int t1 = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (B[i][j] == 0)
				{
					t1 = t1 + 1;

				}
			}
		}
		if (t1 > 0)
		{
			return 0;
		}
		else { return 1; }
	}
	else {
		return 0;
	}
}
int Step2(int leng[8])
{
	int a = 0;

	// Let Temp_Matrix be a 4*4 matrix  and each  element can be expressed as sum array.  
	int Temp_Matrix[4][4][N] = { 0 };
	transformation(Temp_Matrix, 1, leng[0]);
	for (int i = 1; i < 8; i++)
	{
		int Elementary_TypeIII[4][4][N] = { 0 };
		transformation(Elementary_TypeIII, i+1, leng[i]);
		matrixmult(Elementary_TypeIII, Temp_Matrix, Temp_Matrix);
	}
	a = MDS(Temp_Matrix);
	return a;

}
void Printfpath(int leng[8])
{
	for (int j = 0; j < 8; j++)
	{
		cout << leng[j] + 1<<" ";
		
	}

	cout << endl;
}


void Linear_operation(int Elementary_number, int alpha, int Matrix[4][4])
{
	if (Elementary_number < 12)
	{
		for (int i = 0; i < 4; i++)
		{
			Matrix[Elementary_type[Elementary_number][1]][i] = Matrix[Elementary_type[Elementary_number][1]][i] + Matrix[Elementary_type[Elementary_number][2]][i] * alpha;
		}
	}
	else
	{
		int c = Elementary_number - 12;

		for (int j = 0; j < 4; j++)
		{
			Matrix[j][Elementary_type[c][1]] = Matrix[j][Elementary_type[c][1]] + Matrix[j][Elementary_type[c][2]] * alpha;
		}

	}

}

void matrixmult(int Matrix_A[4][4][N], int Matrix_B[4][4][N], int Matrix_C[4][4][N])
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int temp1[N] = { 0 }, temp2[N] = { 0 }, temp3[N] = { 0 }, temp4[N] = { 0 };
			multoper(Matrix_A[i][0], Matrix_B[0][j], temp1);
			multoper(Matrix_A[i][1], Matrix_B[1][j], temp2);
			multoper(Matrix_A[i][2], Matrix_B[2][j], temp3);
			multoper(Matrix_A[i][3], Matrix_B[3][j], temp4);
			int temp5[N] = { 0 }, temp6[N] = { 0 };
			addoper(temp1, temp2, temp5);
			addoper(temp3, temp4, temp6);
			int temp7[N] = { 0 };
			addoper(temp5, temp6, temp7);
			for (int k = 0; k < N; k++)
			{
				Matrix_C[i][j][k] = temp7[k];
			}
		}
	}

}

void matrixadd(int Matrix_A[4][4][N], int Matrix_B[4][4][N], int Matrix_C[4][4][N])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			addoper(Matrix_A[i][j], Matrix_B[i][j], Matrix_C[i][j]);
		}
	}
}

void multoper(int alpha_1[N], int alpha_2[N], int alpha_3[N])
{

	int t1 = 0;
	int t2 = 0;
	for (int i = 0; i < N; i++)
	{
		if (alpha_1[i] > 0)
		{
			t1 = t1 + 1;
		}
		if (alpha_2[i] > 0)
		{
			t2 = t2 + 1;
		}
	}
	int d[N] = { 0 };
	int temp[N] = { 0 };
	int t = 0;
	for (int i = 0; i < t1; i++)
	{
		for (int j = 0; j < t2; j++)
		{
			t = alpha_1[i] | alpha_2[j];
			d[t] = d[t] ^ 1;

		}
	}

	t = 0;
	for (int i = N; i >= 0; i--)
	{
		if (d[i] == 1)
		{

			temp[t] = i;
			t = t + 1;

		}
	}

	for (int i = 0; i < N; i++)
	{
		alpha_3[i] = temp[i];
		//printf("%d\n", a[i]);
	}


}

void addoper(int alpha_1[N], int alpha_2[N], int alpha_3[N])
{
	for (int i = 0; i < N; i++)
	{
		//printf("%d,%d\n", a[i],b[i]);
	}
	int c[N] = { 0 };
	int t1 = 0;
	int t2 = 0;
	for (int i = 0; i < N; i++)
	{
		if (alpha_1[i] > 0)
		{
			t1 = t1 + 1;
		}
		if (alpha_2[i] > 0)
		{
			t2 = t2 + 1;
		}
	}
	int t = 0;
	t1 = 0; t2 = 0;
	for (int i = 0; i < N; i++)
	{
		if (alpha_1[t1] > alpha_2[t2])
		{
			c[t] = alpha_1[t1];
			t1 = t1 + 1;
			t = t + 1;
		}
		else if (alpha_1[t1] < alpha_2[t2])
		{
			c[t] = alpha_2[t2];
			t2 = t2 + 1;
			t = t + 1;
		}
		else {
			t1 = t1 + 1;
			t2 = t2 + 1;
		}


	}
	for (int i = 0; i < N; i++)
	{
		alpha_3[i] = c[i];
	}

}

int MDS(int Matrix_A[4][4][N])
{
	int hh[36][4] = {
	0,1,0,1,0,1,0,2,0,1,0,3,0,1,1,2,0,1,1,3,0,1,2,3,
	0,2,0,1,0,2,0,2,0,2,0,3,0,2,1,2,0,2,1,3,0,2,2,3,
	0,3,0,1,0,3,0,2,0,3,0,3,0,3,1,2,0,3,1,3,0,3,2,3,
	1,2,0,1,1,2,0,2,1,2,0,3,1,2,1,2,1,2,1,3,1,2,2,3,
	1,3,0,1,1,3,0,2,1,3,0,3,1,3,1,2,1,3,1,3,1,3,2,3,
	2,3,0,1,2,3,0,2,2,3,0,3,2,3,1,2,2,3,1,3,2,3,2,3
	};
	int gh1[16][3] = {
		0,1,3,0,2,4,1,2,5,3,4,5,
		0,1,3,0,2,4,1,2,5,3,4,5,
		6,7,9,6,8,10,7,8,11,9,10,11,
		18,19,21,18,20,22,19,20,23,21,22,23
	};

	int gh2[16][3] = {
		2,1,0,3,1,0,3,2,0,3,2,1,
		2,1,0,3,1,0,3,2,0,3,2,1,
		2,1,0,3,1,0,3,2,0,3,2,1,
		2,1,0,3,1,0,3,2,0,3,2,1
	};
	int hg[4][3] = {
		0, 1, 2, 0, 1, 3, 0, 2, 3, 1, 2, 3 };
	int c[N] = { 0 }, d[N] = { 0 }, e[N] = { 0 }, f[N] = { 0 }, g[N] = { 0 };
	int temp[36][N];
	int tt = 0;
	// Verify the determinants of the 36 submatrices of order two 
	for (int i = 0; i < 36; i++)
	{
		multoper(Matrix_A[hh[i][0]][hh[i][2]], Matrix_A[hh[i][1]][hh[i][3]], c);
		multoper(Matrix_A[hh[i][1]][hh[i][2]], Matrix_A[hh[i][0]][hh[i][3]], d);
		addoper(c, d, e);
		int t = 0;
		for (int j = 0; j < N; j++)
		{
			temp[i][j] = e[j];
			if (e[j] > 0)
			{
				t = t + 1;
				
			}
		}
		if (t > 0)
		{
			tt = tt + 1;
		}
	}
	if (tt == 36)
	{
		// Verify the determinants of the 16 submatrices of order three 
		for (int i = 0; i < 4; i++)
		{
			multoper(temp[gh1[i][0]], Matrix_A[2][gh2[i][0]], c);
			multoper(temp[gh1[i][1]], Matrix_A[2][gh2[i][1]], d);
			multoper(temp[gh1[i][2]], Matrix_A[2][gh2[i][2]], e);
			addoper(c, d, f);
			addoper(e, f, g);
			int t = 0;
			for (int j = 0; j < N; j++)
			{

				if (g[j] > 0)
				{
					t = t + 1;
					//printf("%d,", g[j]);
				}
			}
			//printf("\n");

			if (t > 0)
			{
				tt = tt + 1;

			}

		}

		for (int i = 4; i < 16; i++)
		{
			multoper(temp[gh1[i][0]], Matrix_A[3][gh2[i][0]], c);
			multoper(temp[gh1[i][1]], Matrix_A[3][gh2[i][1]], d);
			multoper(temp[gh1[i][2]], Matrix_A[3][gh2[i][2]], e);
			addoper(c, d, f);
			addoper(e, f, g);
			int t = 0;
			for (int j = 0; j < N; j++)
			{
				if (g[j] > 0)
				{
					t = t + 1;
				}

			}
			//printf("\n");
			if (t > 0)
			{
				tt = tt + 1;

			}
		}

		if (tt == 52)
		{
			return  1;
		}
		else{ return  0; }
	}
	else { return 0; }
}
int Integer_power(int num)
{
	int s = 1;
	for (int i = 0; i < num; i++)
	{
		s = s * 2;
	}
	return s;

}
void soft(int array[N], int j)
{


	int b[N] = { 0 };
	qsort(array, N, sizeof(array[0]), cmp);

	for (int i = 0; i < N; i++)
	{
		b[i] = array[N - 1 - i];
	}

	for (int i = 0; i < N; i++)
	{
		array[i] = b[i];
		//printf("%d\n", array[i]);
	}
}
int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

void transformation(int Matrix_A[4][4][N], int alpha, int Elementary_number)
{
	Matrix_A[0][0][0] = 1;
	Matrix_A[1][1][0] = 1;
	Matrix_A[2][2][0] = 1;
	Matrix_A[3][3][0] = 1;
	Matrix_A[Elementary_type[Elementary_number][1]][Elementary_type[Elementary_number][2]][0] = Integer_power(alpha);
}

