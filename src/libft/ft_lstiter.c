#include "libft.h"

void	ft_lstiter(t_node *lst, void (*f)(void *))
{
	if (f)
	{
		while (lst)
		{
			f(lst->key);
			f(lst->value);
			lst = lst -> next;
		}
	}
}
