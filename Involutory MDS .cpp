
#include "pch.h"
#include <iostream>
#include<stdio.h>
using namespace std;
int Judge_innov(int Matrix[4][4]);
int mult[16][16] = {
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
	 0, 2, 4, 6, 8,10,12,14, 3, 1, 7, 5,11, 9,15,13,
	 0, 3, 6, 5,12,15,10, 9,11, 8,13,14, 7, 4, 1, 2,
	 0, 4, 8,12, 3, 7,11,15, 6, 2,14,10, 5, 1,13, 9,
	 0, 5,10,15, 7, 2,13, 8,14,11, 4, 1, 9,12, 3, 6,
	 0, 6,12,10,11,13, 7, 1, 5, 3, 9,15,14, 8, 2, 4,
	 0, 7,14, 9,15, 8, 1, 6,13,10, 3, 4, 2, 5,12,11,
	 0, 8, 3,11, 6,14, 5,13,12, 4,15, 7,10, 2, 9, 1,
	 0, 9, 1, 8, 2,11, 3,10, 4,13, 5,12, 6,15, 7,14,
	 0,10, 7,13,14, 4, 9, 3,15, 5, 8, 2, 1,11, 6,12,
	 0,11, 5,14,10, 1,15, 4, 7,12, 2, 9,13, 6, 8, 3,
	 0,12,11, 7, 5, 9,14, 2,10, 6, 1,13,15, 3, 4, 8,
	 0,13, 9, 4, 1,12, 8, 5, 2,15,11, 6, 3,14,10, 7,
	 0,14,15, 1,13, 3, 2,12, 9, 7, 6, 8, 4,10,11, 5,
	 0,15,13, 2, 9, 6, 4,11, 1,14,12, 3, 8, 7, 5,10 };
int add[16][16] = {
	0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	1,  0,  3,  2,  5,  4,  7,  6,  9,  8, 11, 10, 13, 12, 15, 14,
	2,  3,  0,  1,  6,  7,  4,  5, 10, 11,  8,  9, 14, 15, 12, 13,
	3,  2,  1,  0,  7,  6,  5,  4, 11, 10,  9,  8, 15, 14, 13, 12,
	4,  5,  6,  7,  0,  1,  2,  3, 12, 13, 14, 15,  8,  9, 10, 11,
	5,  4,  7,  6,  1,  0,  3,  2, 13, 12, 15, 14,  9,  8, 11, 10,
	6,  7,  4,  5,  2,  3,  0,  1, 14, 15, 12, 13, 10, 11,  8,  9,
	7,  6,  5,  4,  3,  2,  1,  0, 15, 14, 13, 12, 11, 10,  9,  8,
	8,  9, 10, 11, 12, 13, 14, 15,  0,  1,  2,  3,  4,  5,  6,  7,
	9,  8, 11, 10, 13, 12, 15, 14,  1,  0,  3,  2,  5,  4,  7,  6,
	10, 11,  8,  9, 14, 15, 12, 13,  2,  3,  0,  1,  6,  7,  4,  5,
	11, 10,  9,  8, 15, 14, 13, 12,  3,  2,  1,  0,  7,  6,  5,  4,
	12, 13, 14, 15,  8,  9, 10, 11,  4,  5,  6,  7,  0,  1,  2,  3,
	13, 12, 15, 14,  9,  8, 11, 10,  5,  4,  7,  6,  1,  0,  3,  2,
	14, 15, 12, 13, 10, 11,  8,  9,  6,  7,  4,  5,  2,  3,  0,  1,
	15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0
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
int T_Mset[16][4] ={
	2,2,2,2,2,2,2,9,2,2,9,2,2,2,9,9,
	2,9,2,2,2,9,2,9,2,9,9,2,2,9,9,9,
	9,2,2,2,9,2,2,9,9,2,9,2,9,2,9,9,
	9,9,2,2,9,9,2,9,9,9,9,2,9,9,9,9,

};
int Elementary_type[12][3] = {
	0, 0, 1, 1, 0, 2, 2, 0, 3, 3, 1, 0,  4, 1, 2,  5, 1, 3,
	6, 2, 0, 7, 2, 1, 8, 2, 3, 9, 3, 0, 10, 3, 1, 11, 3, 2,
};
void Linear_operation(int Elementary_number, int alpha, int Matrix[4][4]);

void Eight_four_MDS(int path[8], int alpha[4], int Elementary_TypeI[4][4]);
void Matrix_mult(int Ma[4][4], int B[4][4]);
int Judge_MDS(int M[4][4]);
int Identity_Matrix[4][4] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
int Elementary_TypeI_Class[24][4][4] = { 
1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,
1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,
1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,
1,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,
1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,
1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,
0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,
0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,
0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,
0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,
0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,
0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,
0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,
0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,
0,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,
0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,
0,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,
0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,
0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,
0,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,
0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,
0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,
0,0,0,1,1,0,0,0,0,0,1,0,0,1,0,0
};
void Generator_Matrix84(int position[4], int alpha[4], int path[8], int Elementary_TypeI[4][4], int temp_Matrix[4][4]);

void main()
{
	
	for (int i = 7; i < 8; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				Eight_four_MDS(path[j], T_Mset[k], Elementary_TypeI_Class[i]);
			}
		}
	}
	
	
}

void Eight_four_MDS(int path[8], int alpha[4], int Elementary_TypeI[4][4])
{
	for (int l = 0; l < 41; l++)
	{
		for (int i = l + 1; i < 42; i++)
		{
			for (int j = i + 1; j < 43; j++)
			{
				for (int k = j + 1; k < 44; k++)
				{
					int temp_Matrix[4][4] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
					int position[4] = { l,i,j,k };
					Generator_Matrix84(position, alpha, path, Elementary_TypeI, temp_Matrix);

					if (Judge_MDS(temp_Matrix) == 1 && Judge_innov(temp_Matrix) == 1)
					{
						for (int i1 = 0; i1 < 4; i1++)
						{
						
							for (int j1 = 0; j1 < 4; j1++)
							{
								cout << hex << temp_Matrix[i1][j1];
								
							}
							cout << endl;

						}
					
						cout << endl;

					}
				}
			}
		}
	}

}

void Generator_Matrix84(int position[4], int alpha[4], int path[8], int Elementary_TypeI[4][4], int temp_Matrix[4][4])
{

	int b[44] = { 0 };
	for (int i = 0; i < 44; i++)
	{
		b[i] = 1;
	}
	for (int i = 0; i < 44; i++)
	{
		b[i] = 1;
	}

	b[position[0]] = alpha[0]; b[position[1]] = alpha[1]; b[position[2]] = alpha[2]; b[position[3]] = alpha[3];

	for (int i1 = 0; i1 < 8; i1++)
	{
		int Elementary_TypeII[4][4] = { 0 };
		Elementary_TypeII[0][0] = b[4 * i1]; Elementary_TypeII[1][1] = b[4 * i1 + 1]; Elementary_TypeII[2][2] = b[4 * i1 + 2]; Elementary_TypeII[3][3] = b[4 * i1 + 3];
		Matrix_mult(temp_Matrix, Elementary_TypeII);

		Linear_operation(path[i1] - 1, b[36 + i1], temp_Matrix);

	}
	int Elementary_TypeII[4][4] = { 0 };
	Elementary_TypeII[0][0] = b[32]; Elementary_TypeII[1][1] = b[33]; Elementary_TypeII[2][2] = b[34]; Elementary_TypeII[3][3] = b[35];
	Matrix_mult(temp_Matrix, Elementary_TypeII);
	Matrix_mult(temp_Matrix, Elementary_TypeI);
}

void Matrix_mult(int Matrix_A[4][4], int Matrix_B[4][4])
{
	int C[4][4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				C[i][j] = add[C[i][j]][mult[Matrix_B[i][k]][Matrix_A[k][j]]];
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Matrix_A[i][j] = C[i][j];
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
	int g[53];
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
	int t = 0;
	for (int i = 0; i < 52; i++)
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
int Judge_innov(int Matrix[4][4])
{
	int c[4][4] = { 0 };
	int B[4][4] = { 0 };
	int i, j, k;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 4; k++)
			{
				c[i][j] = c[i][j] ^ mult[Matrix[i][k]][Matrix[k][j]];
			}

		}
	}
	int t = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			B[i][j] = c[i][j] ^ Identity_Matrix[i][j];
			if (B[i][j] == 0)
			{
				t = t + 1;
			}
		}
	}
	if (t == 16)
	{
		return 1;
	}
	else
	{
		return 0;
	}



}
























