#include "libft.h"

void	ft_lstdelone(t_node *lst, void (*del)(void *))
{
	if (lst && del)
	{
		if (lst->key)
			del(lst->key);
		if (lst->value)
			del(lst->value);
		if (lst->env_line)
			del(lst->env_line);
		free(lst);
	}
}
