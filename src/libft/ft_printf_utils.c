/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou  <mmanssou@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/09/13 15:23:59 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_printf(char *str)
{
	size_t	count;

	count = 0;
	if (str)
	{
		while (*str)
		{
			str++;
			count++;
		}
	}
	return (count);
}

int	ft_put_address(int fd, unsigned long long nbr)
{
	int	chars_printed;

	chars_printed = 0;
	if (!nbr)
	{
		chars_printed += ft_putstr_printf(fd, NULLABLE);
		return (chars_printed);
	}
	chars_printed += ft_putstr_printf(fd, "0x");
	chars_printed += puthex_printf(fd, nbr, 0);
	return (chars_printed);
}

int	puthex_printf(int fd, unsigned long long nbr, int use_uppercase)
{
	int		chars_printed;
	char	*base;

	chars_printed = 0;
	if (use_uppercase)
		base = HEX_UPCASE;
	else
		base = HEX_LWCASE;
	if (nbr < 16)
		chars_printed += putchar_printf(fd, base[nbr]);
	else
	{
		chars_printed += puthex_printf(fd, nbr / 16, use_uppercase);
		chars_printed += puthex_printf(fd, nbr % 16, use_uppercase);
	}
	return (chars_printed);
}

int	put_base_printf(int fd, long long nbr, char *base)
{
	int	len_base;
	int	chars_printed;

	chars_printed = 0;
	len_base = ft_strlen_printf(base);
	if (nbr < 0)
	{
		nbr *= -1;
		chars_printed += putchar_printf(fd, '-');
	}
	if (nbr < len_base)
		chars_printed += putchar_printf(fd, base[nbr]);
	else
	{
		chars_printed += put_base_printf(fd, nbr / len_base, base);
		chars_printed += put_base_printf(fd, nbr % len_base, base);
	}
	return (chars_printed);
}

int	ft_putstr_printf(int fd, char *str)
{
	int	chars_printed;

	chars_printed = 0;
	if (str)
	{
		while (str[chars_printed])
		{
			write(fd, &str[chars_printed], 1);
			chars_printed++;
		}
	}
	else
		chars_printed += ft_putstr_printf(fd, "(null)");
	return (chars_printed);
}
