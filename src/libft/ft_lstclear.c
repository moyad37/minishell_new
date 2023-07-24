#include "libft.h"

void	ft_lstclear(t_node **lst, void (*del)(void *))
{
	t_node	*store_previous_node;

	store_previous_node = *lst;
	if (del)
	{
		while (*lst != 0 && store_previous_node != 0)
		{
			store_previous_node = *lst;
			*lst = (*lst)->next;
			del(store_previous_node->key);
			del(store_previous_node->value);
			free(store_previous_node);
		}
		lst = NULL;
	}
}
