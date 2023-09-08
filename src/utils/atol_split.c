#include "../../inc/minishell.h"


long int	ft_latoi(const char *nptr)
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
			return (0);
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

static int	space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	count(char const *s)
{
	int count;

	count = 0;
	while (!space(*s) && *s)
	{
		s++;
		count++;
	}
	return (count);
}

static int	counterWords(char const *s)
{
	int count;

	count = 0;
	while (*s)
	{
		if (!space(*s))
			count++;
		while (!space(*s) && *s)
			s++;
		while (space(*s) && *s)
			s++;
	}
	return (count);
}

char	**ft_split2(char const *s)
{
	int i;
	int words;
	int len_current_word;
	char **splitted_string;

	i = 0;
	if (!s)
		return (NULL);
	words = counterWords(s);
	splitted_string = ft_calloc(words + 1, sizeof(char *));
	while (*s && words != 0)
	{
		if (!space(*s))
		{
			len_current_word = count(s);
			*(splitted_string + i) = ft_substr(s, 0, len_current_word);
			i++;
		}
		while (!space(*s) && *s)
			s++;
		while (space(*s) && *s)
			s++;
	}
	return (splitted_string);
}
