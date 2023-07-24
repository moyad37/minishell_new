#include "libft.h"

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*last_node;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last_node = ft_lstlast(*lst);
			last_node -> next = new;
		}
	}
}
