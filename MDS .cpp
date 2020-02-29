
#include "pch.h"
#include <iostream>
#include<stdio.h>
#define N 4
#define M 16

using namespace std;
int Initialization[4][4] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
int Elementary_type[12][3] = {
	0, 0, 1, 1, 0, 2, 2, 0, 3, 3, 1, 0,  4, 1, 2,  5, 1, 3,
	6, 2, 0, 7, 2, 1, 8, 2, 3, 9, 3, 0, 10, 3, 1, 11, 3, 2,
};
//------------------------------------------------------------------
//Primitive polynomial is alpha ^ 4 + alpha + 1 = 0 and n = 4
// Lines 17 to 5 can be changed. For example, the polynomial is alpha ^ 8 + alpha ^ 2 + 1 = 0.
// Multiplication table mult[256][256] and addition table add[256][256] should
// be obtained and the value of inv is 131.
#define inv 9
int mult[16][16] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
0, 2, 4, 6, 8, 10, 12, 14, 3, 1, 7, 5, 11, 9, 15, 13,
0, 3, 6, 5, 12, 15, 10, 9, 11, 8, 13, 14, 7, 4, 1, 2,
0, 4, 8, 12, 3, 7, 11, 15, 6, 2, 14, 10, 5, 1, 13, 9,
0, 5, 10, 15, 7, 2, 13, 8, 14, 11, 4, 1, 9, 12, 3, 6,
0, 6, 12, 10, 11, 13, 7, 1, 5, 3, 9, 15, 14, 8, 2, 4,
0, 7, 14, 9, 15, 8, 1, 6, 13, 10, 3, 4, 2, 5, 12, 11,
0, 8, 3, 11, 6, 14, 5, 13, 12, 4, 15, 7, 10, 2, 9, 1,
0, 9, 1, 8, 2, 11, 3, 10, 4, 13, 5, 12, 6, 15, 7, 14,
0, 10, 7, 13, 14, 4, 9, 3, 15, 5, 8, 2, 1, 11, 6, 12,
0, 11, 5, 14, 10, 1, 15, 4, 7, 12, 2, 9, 13, 6, 8, 3,
0, 12, 11, 7, 5, 9, 14, 2, 10, 6, 1, 13, 15, 3, 4, 8,
0, 13, 9, 4, 1, 12, 8, 5, 2, 15, 11, 6, 3, 14, 10, 7,
0, 14, 15, 1, 13, 3, 2, 12, 9, 7, 6, 8, 4, 10, 11, 5,
0, 15, 13, 2, 9, 6, 4, 11, 1, 14, 12, 3, 8, 7, 5, 10,
};
int add[16][16] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14,
2, 3, 0, 1, 6, 7, 4, 5, 10, 11, 8, 9, 14, 15, 12, 13,
3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12,
4, 5, 6, 7, 0, 1, 2, 3, 12, 13, 14, 15, 8, 9, 10, 11,
5, 4, 7, 6, 1, 0, 3, 2, 13, 12, 15, 14, 9, 8, 11, 10,
6, 7, 4, 5, 2, 3, 0, 1, 14, 15, 12, 13, 10, 11, 8, 9,
7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8,
8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7,
9, 8, 11, 10, 13, 12, 15, 14, 1, 0, 3, 2, 5, 4, 7, 6,
10, 11, 8, 9, 14, 15, 12, 13, 2, 3, 0, 1, 6, 7, 4, 5,
11, 10, 9, 8, 15, 14, 13, 12, 3, 2, 1, 0, 7, 6, 5, 4,
12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3,
13, 12, 15, 14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2,
14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1,
15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
};
//-------------------------------------------------------------------
int T_Mset_one[8][3] = {
	2,2,2,2,2,inv,2,inv,2,inv,2,2,2,inv,inv,inv,2,inv,inv,inv,2,inv,inv,inv
};
int path[32][8] ={
9,1,5,7,11,3,4,12,
9,1,5,7,11,3,12,4,
9,1,5,10,1,9,5,10,
9,1,5,10,1,9,10,5,
9,1,5,10,9,1,5,10,
9,1,5,10,9,1,10,5,
9,1,5,11,7,3,4,12,
9,1,5,11,7,3,12,4,
9,1,10,2,6,8,4,12,
9,1,10,2,6,8,12,4,
9,1,10,5,1,9,5,10,
9,1,10,5,1,9,10,5,
9,1,10,5,9,1,5,10,
9,1,10,5,9,1,10,5,
9,1,10,6,2,8,4,12,
9,1,10,6,2,8,12,4,
9,4,2,8,10,6,1,12,
9,4,2,8,10,6,12,1,
9,4,2,10,8,6,1,12,
9,4,2,10,8,6,12,1,
9,4,2,11,4,9,2,11,
9,4,2,11,4,9,11,2,
9,4,2,11,9,4,2,11,
9,4,2,11,9,4,11,2,
9,4,11,2,4,9,2,11,
9,4,11,2,4,9,11,2,
9,4,11,2,9,4,2,11,
9,4,11,2,9,4,11,2,
9,4,11,3,5,7,1,12,
9,4,11,3,5,7,12,1,
9,4,11,5,3,7,1,12,
9,4,11,5,3,7,12,1,
};

void Linear_operation(int Elementary_number, int alpha, int Matrix[4][4]);
void Matrix_mult(int Matrix_A[4][4], int Matrix_B[4][4]);
int Judge_MDS(int Matrix[4][4]);
 
void Eight_Three_MDS(int path[8], int T_M[3]);



void Generator_Matrix83(int position[3], int T_M[3], int path[8], int Temp_Matrix[4][4]);

void main()
{
	for (int k = 0; k < 32; k++)
	{
		for (int i = 0; i < 8; i++)
		{
			int T_M[3] = { T_Mset_one[i][0],T_Mset_one[i][1],T_Mset_one[i][2] };
			Eight_Three_MDS(path[k], T_M);
		}
		
	}

}

void Eight_Three_MDS(int path[8],int T_M[3])
{
	int b[36] = { 0 };
	for (int i = 0; i < 36; i++)
	{
		b[i] = 1;
	}
	for (int i = 0; i < 34; i++)
	{
		for (int j = i + 1; j < 35; j++)
		{
			for (int k = j + 1; k < 36; k++)
			{
				
				int Temp_Matrix[4][4] = { 0 };
				
				int position[3] = { i,j,k };

				Generator_Matrix83(position, T_M, path, Temp_Matrix);

				if (Judge_MDS(Temp_Matrix) == 1)
				{
					for (int j1 = 0; j1 < 4; j1++)
					{
						for (int k1 = 0; k1 < 4; k1++)
						{
							cout << hex<< Temp_Matrix[j1][k1]<<"  ";
						}
						cout << endl;

					}
					cout << endl;
				}
		
			}
			
		}
		
	}
	

}

void Generator_Matrix83(int position[3], int T_M[3], int path[8], int Temp_Matrix[4][4])
{

	int b[36] = { 0 };
	for (int i = 0; i < 36; i++)
	{
		b[i] = 1;
	}

	b[position[0]] = T_M[0]; b[position[1]] = T_M[1]; b[position[2]] = T_M[2]; 

	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int j1 = 0; j1 < 4; j1++)
		{
			Temp_Matrix[i1][j1] = Initialization[i1][j1];
		}
	}
	Linear_operation(path[0] - 1, b[28], Temp_Matrix);
	for (int i1 = 0; i1 < 7; i1++)
	{
		int TypeII_Elementary[4][4] = { 0 };
		TypeII_Elementary[0][0] = b[4 * i1]; TypeII_Elementary[1][1] = b[4 * i1 + 1]; TypeII_Elementary[2][2] = b[4 * i1 + 2]; TypeII_Elementary[3][3] = b[4 * i1 + 3];
		Matrix_mult(Temp_Matrix, TypeII_Elementary);

		Linear_operation(path[i1 + 1] - 1, b[29 + i1], Temp_Matrix);

	}
}

void Matrix_mult(int Matrix_A[4][4], int Matrix_B[4][4])
{
	int Matrix_C[4][4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				Matrix_C[i][j] = add[Matrix_C[i][j]][mult[Matrix_B[i][k]][Matrix_A[k][j]]];
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Matrix_A[i][j] = Matrix_C[i][j];
		}
	}

}
void Linear_operation(int Elementary_number, int alpha, int Matrix[4][4])
{
	if (Elementary_number < 12)
	{
		for (int i = 0; i < 4; i++)
		{
			Matrix[Elementary_type[Elementary_number][1]][i] = add[Matrix[Elementary_type[Elementary_number][1]][i]][mult[Matrix[Elementary_type[Elementary_number][2]][i]][alpha]];
		}
	}
	else
	{
		int c = Elementary_number - 12;

		for (int j = 0; j < 4; j++)
		{
			Matrix[j][Elementary_type[c][1]] = add[Matrix[j][Elementary_type[c][1]]][mult[Matrix[j][Elementary_type[c][2]]][alpha]];
		}

	}

}

int Judge_MDS(int Matrix[4][4])
{
	int hh[36][4] = {
	0,1,0,1,0,1,0,2,0,1,0,3,0,1,1,2,0,1,1,3,0,1,2,3,
	0,2,0,1,0,2,0,2,0,2,0,3,0,2,1,2,0,2,1,3,0,2,2,3,
	0,3,0,1,0,3,0,2,0,3,0,3,0,3,1,2,0,3,1,3,0,3,2,3,
	1,2,0,1,1,2,0,2,1,2,0,3,1,2,1,2,1,2,1,3,1,2,2,3,
	1,3,0,1,1,3,0,2,1,3,0,3,1,3,1,2,1,3,1,3,1,3,2,3,
	2,3,0,1,2,3,0,2,2,3,0,3,2,3,1,2,2,3,1,3,2,3,2,3
	};
	int hg[4][3] = {
		0, 1, 2, 0, 1, 3, 0, 2, 3, 1, 2, 3 };
	int c, d, e, m;
	int g[68] = { 0 };
	int a[3][3];
	int b[3];
	for (int i = 0; i < 36; i++)
	{
		c = Matrix[hh[i][0]][hh[i][2]];
		d = Matrix[hh[i][1]][hh[i][3]];
		e = Matrix[hh[i][1]][hh[i][2]];
		m = Matrix[hh[i][0]][hh[i][3]];
		g[i] = add[mult[c][d]][mult[e][m]];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)

				{
					a[k][l] = Matrix[hg[i][k]][hg[j][l]];
				}
			}
			b[0] = add[mult[a[1][1]][a[2][2]]][mult[a[1][2]][a[2][1]]];
			b[1] = add[mult[a[1][0]][a[2][2]]][mult[a[1][2]][a[2][0]]];
			b[2] = add[mult[a[1][1]][a[2][0]]][mult[a[1][0]][a[2][1]]];
			g[36 + 4 * i + j] = add[add[mult[b[0]][a[0][0]]][mult[a[0][1]][b[1]]]][mult[a[0][2]][b[2]]];

		}


	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			g[52 + 4 * i + j] = Matrix[i][j];
		}
	}
	int t = 0;
	for (int i = 0; i < 68; i++)
	{

		if (g[i] == 0)
		{
			t = t + 1;

		}

	}
	if (t == 0)
	{
		return  1;
	}
	else
	{
		return  0;
	}
}






















