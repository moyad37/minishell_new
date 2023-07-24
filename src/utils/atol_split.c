#include "../../inc/minishell.h"

long int ft_latoi(const char *nptr)
{
    int i = 0;
    long int res = 0;
    int sign = 1;
    while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
        i++;
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            sign = -1;
        i++;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        if (((res * sign * 10) + (nptr[i] - '0') * sign) / 10 != res * sign)
            return 0;
        res = res * 10 + nptr[i] - '0';
        i++;
    }
    return res * sign;
}


static int	count_words(const char *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
			words++;
		while (*s && *s != c)
			s++;
	}
	return (words);
}

char	**ft_split_old(const char *str, char c)
{
	int		i;
	char	**lst;
	size_t	curr_word_len;

	i = 0;
	if (!str)
		return (0);
	lst = (char **)ft_calloc(sizeof(char *), count_words(str, c) + 1);
	if (!lst)
		return (0);
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
		{
			if (!ft_strchr(str, c))
				curr_word_len = ft_strlen((char *)str);
			else
				curr_word_len = ft_strchr(str, c) - str;
			lst[i++] = ft_substr(str, 0, curr_word_len);
			str += curr_word_len;
		}
	}
	return (lst);
}
