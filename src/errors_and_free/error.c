
#include "../../inc/minishell.h"


int	ft_put_address(int fd, unsigned long long nbr);
int	puthex_printf(int fd, unsigned long long nbr, int use_uppercase);
int	put_base_printf(int fd, long long nbr, char *base);
int	ft_putstr_printf(int fd, char *str);
int	putchar_printf(int fd, char c);
static int	ft_percent_handler(char c, va_list ptr, int fd);

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




























int	putchar_printf(int fd, char c)
{
	return (write(fd, &c, 1));
}

static int	ft_percent_handler(char c, va_list ptr, int fd)
{
	int	printed;

	printed = 0;
	if (c == 'c')
		printed += putchar_printf(fd, va_arg(ptr, int));
	else if (c == 's')
		printed += ft_putstr_printf(fd, va_arg(ptr, char *));
	else if (c == 'p')
		printed += ft_put_address(fd, va_arg(ptr, unsigned long long));
	else if (c == 'd' || c == 'i')
		printed += put_base_printf(fd, va_arg(ptr, int), DEC_DIGITS);
	else if (c == 'u')
		printed += put_base_printf(fd, va_arg(ptr, unsigned int), DEC_DIGITS);
	else if (c == 'x')
		printed += put_base_printf(fd, va_arg(ptr, unsigned int), HEX_LWCASE);
	else if (c == 'X')
		printed += put_base_printf(fd, va_arg(ptr, unsigned int), HEX_UPCASE);
	else if (c == '%')
		return (write(fd, "%", 1));
	return (printed);
}

int	ft_printf2(int fd, const char *str, ...)
{
	va_list	ptr;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(ptr, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
			count += ft_percent_handler(str[++i], ptr, fd);
		else
			count += putchar_printf(fd, str[i]);
		i++;
	}
	va_end(ptr);
	return (count);
}
























































int print_error(const char *str, int fd)
{
    int i;

    i = 0;
    if(!str)
        return (2);
    while (str[i++])
        write(fd, &str[i], 1);
    return (2);
}
//err_on_input_redirect
static void	handleInputRedirectError(char *filename)
{
	int	error;

	if (access(filename, F_OK) == -1)
		error = ENOENT;
	else
		error = EACCES;
	
	// ft_putstr_fd("bash: ", 2);
	// ft_putstr_fd(filename, 2);
	// ft_putstr_fd(": ", 2);
	// ft_putstr_fd(strerror(error), 2);
	// ft_putstr_fd("\n", 2);
	
	ft_printf2(STDERR_FILENO, "bash: %s: %s\n", filename, strerror(error));
}
//err_on_output_redirect
static void	handleOutputRedirectError(char *filename)
{
	int	error;

	if (ft_strlen(filename) > 255)
		error = ENAMETOOLONG;
	else
		error = EACCES;
	
	// ft_putstr_fd("bash: ", 2);
	// ft_putstr_fd(filename, 2);
	// ft_putstr_fd(": ", 2);
	// ft_putstr_fd(strerror(error), 2);
	// ft_putstr_fd("\n", 2);	
	
	ft_printf2(STDERR_FILENO, "bash: %s: %s\n", filename, strerror(error));
}

void	handle_error(t_command *cmd, char *filename)
{
	if (cmd->input_fd == -1)
		handleInputRedirectError(filename);
	else if (cmd->output_fd == -1)
		handleOutputRedirectError(filename);
}