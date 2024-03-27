#include <stdio.h>
#include <stdlib.h>

void print_char_arr(char **arr)
{
	for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				printf("%c", arr[i][j]);
			}
			printf("\n");
		}
}


int check_square(char **arr, int x, int y, char num)
{
	int square_x = x/3, square_y = y/3;

	for (int r = square_x * 3; r < square_x * 3 + 3; r++)
	{
		for (int c = square_y * 3; c < square_y * 3 + 3; c++)
		{
			if (arr[r][c] == num)
			{
				return 1;
			}
		}
	}
	
	return 0;
}

int check_row_col(char **arr, int x, int y, char num)
{
	for (int i = 0; i < 9; i++)
	{
		if (arr[x][i] == num || arr[i][y] == num)
		{
			return 1;
		}
	}
	return 0;
}

void rec_core(char **arr, int x, int y, int *pt_sol)
{
	if (arr[x][y] != '.')
	{
		if (x == 8 && y == 8)
		{
			*pt_sol = 1;
		}
		else if (y < 8)
		{
			rec_core(arr, x, y+1, pt_sol);
		}
		else if (x < 8)
		{
			rec_core(arr, x+1, 0, pt_sol);
		}
	}
	else
	{
		for (char num = '1'; num < ':'; num++)
		{
			int cnd1 = check_square(arr, x, y, num);
			int cnd2 = check_row_col(arr, x, y, num);
			
			if (cnd1 == 0 && cnd2 == 0 && *pt_sol == 0)
			{
				arr[x][y] = num;

				if (x == 8 && y == 8)
				{
					*pt_sol = 1;
				}
				else if (y < 8)
				{
					rec_core(arr, x, y+1, pt_sol);
				}
				else if (x < 8)
				{
					rec_core(arr, x+1, 0, pt_sol);
				}
			}
			if (*pt_sol == 0)
			{
				arr[x][y] = '.';
			}
		}
	}
}

int main(int argc, char **argv)
{
	char **arr = (char**) malloc(9 * sizeof(char*));
	for (int i = 0; i < 9; i++)
	{
		arr[i] = (char*) malloc(9 * sizeof(char));
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			arr[i][j] = argv[i+1][j];
		}
	}

	print_char_arr(arr);

	int sol = 0;
	rec_core(arr, 0, 0, &sol);
	
	printf("\n");	
	print_char_arr(arr);

	return 0;
}
