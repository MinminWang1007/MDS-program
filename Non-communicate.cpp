
#include "pch.h"
#include <iostream>
#include "stdlib.h"
#define M 1024
#define N 512
#define n 18

int Integer_power(int num);
int Elementary_type[12][3] = {
	0, 0, 1, 1, 0, 2, 2, 0, 3, 3, 1, 0,  4, 1, 2,  5, 1, 3,
	6, 2, 0, 7, 2, 1, 8, 2, 3, 9, 3, 0, 10, 3, 1, 11, 3, 2,
};
int Step1(int leng[8]);
int leftcase(int a, int b);
int Leftfunction(int a, int b[N]);
int rightcase(int a, int b);
int rightfunction(int a, int b[N]);
void Printfpath(int leng[8]);
void addoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);
void multoper(int alpha_1[N], int alpha_2[N], int alpha_3[N]);
void transformation(int Matrix_A[4][4][N], int alpha, int Elementary_number);
void matrixadd(int Matrix_A[4][4][N], int Matrix_B[4][4][N], int Matrix_C[4][4][N]);
void matrixmult(int Matrix_A[4][4][N], int Matrix_B[4][4][N], int Matrix_C[4][4][N]);
void Linear_operation(int Elementary_number, int alpha, int Matrix[4][4]);
int A[4][4] = { 1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1 };

int  noncommunicate_step2(int leng[8]);
int fourcase(int c1[N], int c2[N], int c3[N], int c4[N]);
int path[M*M][8] = { 0 };
using namespace std;
int main()
{
	
	int B[4][4] = { 0 };
	int tt = 0;
	int t = 0;
	for (int i1 = 0; i1 < 12; i1++)
	{
		cout << i1 << endl;
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
									int a = noncommunicate_step2(leng);
									if (a == 1)
									{
										Printfpath(leng);
										t = t + 1;

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
	cout << t;
	
}

int Step1(int leng[8])
{
	int B[4][4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			B[i][j] = A[i][j];
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

void Printfpath(int leng[8])
{
	for (int j = 0; j < 8; j++)
	{
		cout << leng[j] + 1 << " ";

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

int Integer_power(int num)
{
	int s = 1;
	for (int i = 0; i < num; i++)
	{
		s = s * 2;
	}
	return s;

}
void transformation(int Matrix_A[4][4][N], int alpha, int Elementary_number)
{
	Matrix_A[0][0][0] = 1;
	Matrix_A[1][1][0] = 1;
	Matrix_A[2][2][0] = 1;
	Matrix_A[3][3][0] = 1;
	Matrix_A[Elementary_type[Elementary_number][1]][Elementary_type[Elementary_number][2]][0] = Integer_power(alpha);
}
int nochangeMDS(int A[4][4][N])
{
	int hh[36][4] = {
	0,1,0,1,0,1,0,2,0,1,0,3,0,1,1,2,0,1,1,3,0,1,2,3,
	0,2,0,1,0,2,0,2,0,2,0,3,0,2,1,2,0,2,1,3,0,2,2,3,
	0,3,0,1,0,3,0,2,0,3,0,3,0,3,1,2,0,3,1,3,0,3,2,3,
	1,2,0,1,1,2,0,2,1,2,0,3,1,2,1,2,1,2,1,3,1,2,2,3,
	1,3,0,1,1,3,0,2,1,3,0,3,1,3,1,2,1,3,1,3,1,3,2,3,
	2,3,0,1,2,3,0,2,2,3,0,3,2,3,1,2,2,3,1,3,2,3,2,3
	};
	int c[N] = { 0 }, d[N] = { 0 }, e[N] = { 0 }, f[N] = { 0 }, g[N] = { 0 };
	int temp[36][N];
	int t1 = 0;

	for (int i = 0; i < 4; i++)    //To filter paths which induce matrices that always contain 0
	{
		for (int j = 0; j < 4; j++)
		{

			if (A[i][j][0] > 0)
			{
				t1 = t1 + 1;
			}

		}
	}

	for (int i = 0; i < 36; i++)//Each determinant of the $36$ submatrices of order two is not equal to zero by symbol computation.
	{
		int c1[N] = { 0 }, c2[N] = { 0 }, c3[N] = { 0 }, c4[N] = { 0 };
		for (int k = 0; k < N; k++)
		{
			c1[k] = A[hh[i][0]][hh[i][2]][k];

			c2[k] = A[hh[i][0]][hh[i][3]][k];

			c3[k] = A[hh[i][1]][hh[i][2]][k];

			c4[k] = A[hh[i][1]][hh[i][3]][k];
		}



		multoper(c1, c4, c);
		multoper(c2, c3, d);
		addoper(c, d, e);


		int t = 0;

		
		if (e[0] > 0)
		{

			t1 = t1 + 1;

		}
		
		else
		{
			int h = (c1[0] - 1)*(c2[0] - 1)*(c3[0] - 1)*(c4[0] - 1);
			if (h == 0)
			{
				return 0;
			}
			else {
				if (c1[1] == 0)
				{
					int a1 = 0, b1 = 0;

					a1 = Leftfunction(c1[0], c2);
					b1 = rightfunction(c1[0], c3);
					if (a1 == 1 || b1 == 1)
					{
						return 0;
					}
				}
				if (c2[1] == 0)
				{
					int a2 = 0, b2 = 0;

					a2 = Leftfunction(c2[0], c1);
					b2 = rightfunction(c2[0], c4);
					if (a2 == 1 || b2 == 1)
					{
						return 0;

					}
				}
				if (c3[1] == 0)
				{

					int a3 = 0, b3 = 0;

					a3 = Leftfunction(c3[0], c4);
					b3 = rightfunction(c3[0], c1);
					if (a3 == 1 || b3 == 1)
					{
						return 0;

					}
				}
				if (c4[1] == 0)
				{
					
						int a4 = 0, b4 = 0;

						a4 = Leftfunction(c4[0], c3);
						b4 = rightfunction(c4[0], c2);
						if (a4 == 1 || b4 == 1)
						{
							return 0;

						}


					
				}
				int t = fourcase(c1, c2, c3, c4);
				
				if (t == 0)
				{
					t1 = t1 + 1;
				}


			}

		}

	}

	if (t1 == 52)
	{
		return  1;
	}
	else
	{
		return  0;
	}

}


int Leftfunction(int a, int b[N]) ////decom1(4,68)=0   decom1(64,68)=1 leftfunction
{

	a = a & 0x1fe;
	for (int i = 0; i < N; i++)
	{
		b[i] = b[i] & 0x1fe;
	}


	int t = 0, tt = 0, num = 0;
	for (int i1 = 0; i1 < N; i1++)
	{
		if (b[i1] > 0)
		{
			tt = tt + 1;

		}
		else { break; }
	}

	for (int i1 = 0; i1 < tt; i1++)
	{
		int t = b[i1] ^ a;
		int	temp = leftcase(a, t);
		//printf("%d\n", temp);
		if (temp == 1)
		{
			num = num + 1;
		}
	}

	if (num == tt)
	{
		return 1;
	}
	else { return 0; }
}
int rightfunction(int a, int b[N])//decom1(4,68)=1   decom1(64,68)=0 rightfunction
{
	a = a & 0x1fe;
	for (int i = 0; i < N; i++)
	{
		b[i] = b[i] & 0x1fe;
	}
	int t = 0, tt = 0, num = 0;
	for (int i1 = 0; i1 < N; i1++)
	{
		if (b[i1] > 0)
		{
			tt = tt + 1;

		}
		else { break; }
	}

	for (int i1 = 0; i1 < tt; i1++)
	{
		int t = b[i1] ^ a;
		int	temp = rightcase(a, t);
		//printf("%d\n", temp);
		if (temp == 1)
		{
			num = num + 1;
		}
	}

	if (num == tt)
	{
		return 1;
	}
	else { return 0; }
}
int rightcase(int a, int b)
{
	int t = 0, t1 = 0;
	for (int i = 0; i < 7; i++)
	{
		t1 = b * Integer_power(i);
		int num = a & t1;
		if (num == 0)
		{
			t = t + 1;
		}
	}


	if (t == 7)
	{
		return 1;
	}
	else { return 0; }
}
int leftcase(int a, int b)//case2(4,64)=1  case2(64,4)=0
{
	int t = 0, t1 = 0;
	for (int i = 0; i < 7; i++)
	{
		t1 = b / Integer_power(i);
		int num = a & t1;
		if (num == 0)
		{
			t = t + 1;
		}
	}

	if (t == 7)
	{
		return 1;
	}
	else { return 0; }
}


int noncommunicate_step2(int leng[8])
{
	int h = (leng[0] ^ leng[1])*(leng[2] ^ leng[1])*(leng[2] ^ leng[3])*(leng[3] ^ leng[4])*(leng[4] ^ leng[5])*(leng[6] ^ leng[5])*(leng[7] ^ leng[6]);
	if (h == 0)
	{
		return 0;
	}
	int a = 0;
	int Temp_Matrix[4][4][N] = { 0 };
	transformation(Temp_Matrix, 1, leng[0]);
	for (int i = 1; i < 8; i++)
	{
		int Elementary_TypeIII[4][4][N] = { 0 };
		transformation(Elementary_TypeIII, i + 1, leng[i]);
		matrixmult(Elementary_TypeIII, Temp_Matrix, Temp_Matrix);
	}

	a = nochangeMDS(Temp_Matrix);
	return a;

}

int fourcase(int c1[N], int c2[N], int c3[N], int c4[N])
{
	int t1=0, t2=0, t3=0, t4=0;
	for (int i = 0; i < N; i++)
	{
		int t1 = 0;
		if (c1[N] > 0)
		{
			c1[N] = c1[N] & 0x1fe;
			t1 = t1 + 1;
		}
	}
	for (int i = 0; i < N; i++)
	{
		int t2 = 0;
		if (c2[N] > 0)
		{
			c2[N] = c2[N] & 0x1fe;
			t2 = t2 + 1;
		}
	}
	for (int i = 0; i < N; i++)
	{
		int t3 = 0;
		if (c3[N] > 0)
		{
			c3[N] = c3[N] & 0x1fe;
			t3 = t3 + 1;
		}
	}
	for (int i = 0; i < N; i++)
	{
		int t4 = 0;
		if (c4[N] > 0)
		{
			c4[N] = c4[N] & 0x1fe;
			t4 = t4 + 1;
		}
	}
	if (t1 != t2 || t1 != t3)
	{
		return 0;
	}
	else {
		if (t1 == t2)
		{
			int temp1[N] = { 0 }, temp2[N] = { 0 };
			for (int i = 0; i < t1; i++)
			{
				temp1[i] = c1[i] ^ c2[i];

			}
			for (int i = 0; i < t3; i++)
			{
				temp2[i] = c3[i] ^ c4[i];

			}
			int t = 1;
			for (int i = 1; i < t1; i++)
			{
				if (temp1[0] == temp1[i])
				{
					t = t * 1;
				}
				else { t = t * 0; }
			}
			for (int i = 0; i < t2; i++)
			{
				if (temp1[0] == temp2[i])
				{
					t = t * 1;
				}
				else { t = t * 0; }
			}
			if (t == 1 || Leftfunction(temp1[0], c1) == 1)
			{
				return 1;
			}
			else { return 0; }
		}

		if (t1 == t3)
		{
			int temp1[N] = { 0 }, temp2[N] = { 0 };
			for (int i = 0; i < t1; i++)
			{
				temp1[i] = c1[i] ^ c3[i];

			}
			for (int i = 0; i < t2; i++)
			{
				temp2[i] = c2[i] ^ c4[i];

			}
			int t = 1;
			for (int i = 1; i < t1; i++)
			{
				if (temp1[0] == temp1[i])
				{
					t = t * 1;
				}
				else { t = t * 0; }
			}
			for (int i = 0; i < t2; i++)
			{
				if (temp1[0] == temp2[i])
				{
					t = t * 1;
				}
				else { t = t * 0; }
			}
			if (t == 1 || rightfunction(temp1[0], c1) == 1)
			{
				return 1;
			}
			else { return 0; }
		}
	
	}

}








