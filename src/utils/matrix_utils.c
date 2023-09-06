#include "../../inc/minishell.h"

// void	ft_free_matrix(void **matrix)
// {
// 	int	i;
// 	int	matrix_len;

// 	i = 0;
// 	matrix_len = matrixCounter(matrix);
// 	while (i < matrix_len)
// 	{
// 		free(matrix[i]);
// 		i++;
// 	}
// 	free(matrix);
// }

void	FreeMatrix_size_n(void **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	free(matrix);
}


int	matrixCounter(void **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}

void	ft_free_spatial_matrix(void ***matrix)
{
	int	i;
	int	j;
	int	matr_len;

	i = 0;
	matr_len = matrixCounter(*matrix);
	while (i < matr_len)
	{
		j = 0;
		while (matrix[i][j])
		{
			free(matrix[i][j]);
			j++;
		}
		free(matrix[i]);
		i++;
	}
	free(matrix);
}