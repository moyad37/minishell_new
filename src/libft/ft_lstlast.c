#include "libft.h"

t_node	*ft_lstlast(t_node *lst)
{
	if (!lst)
		return (0);
	while (lst -> next != 0)
		lst = lst -> next;
	return (lst);
}
