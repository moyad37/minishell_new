#include "../inc/minishell.h"

void	ft_free_matrix(void **matrix)
{
	int	i;
	int	matrix_len;

	i = 0;
	matrix_len = ft_count_matrix(matrix);
	while (i < matrix_len)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	ft_free_matrix_size_n(void **matrix, int size)
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

void	ft_free_list(t_node **head)
{
	t_node	*current;
	t_node	*next;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		if (current->env_line)
			free(current->env_line);
		free(current);
		current = next;
	}
	*head = NULL;
}

int	ft_count_matrix(void **matrix)
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
	matr_len = ft_count_matrix(*matrix);
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