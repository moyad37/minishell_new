#include "../../inc/minishell.h"

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	FreeMatrix(void **matrix)
{
	int	i;
	int	matrix_len;

	i = 0;
	matrix_len = matrixCounter(matrix);
	while (i < matrix_len)
	{
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