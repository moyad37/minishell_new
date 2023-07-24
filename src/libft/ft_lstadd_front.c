#include "libft.h"

void	ft_lstadd_front(t_node **lst, t_node *new)
{
	new -> next = *lst;
	*lst = new;
}
