/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:00:29 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/14 13:01:31 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formats(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += print_char(va_arg(args, int));
	else if (format == 's')
		len += print_string(va_arg(args, char *));
	else if (format == 'p')
		len += print_pointer((unsigned long)va_arg(args, void *));
	else if (format == 'd')
		len += print_d(va_arg(args, int));
	else if (format == 'i')
		len += print_i(va_arg(args, int));
	else if (format == 'u')
		len += print_u(va_arg(args, unsigned int));
	else if (format == 'X')
		len += print_x_upper(va_arg(args, unsigned int));
	else if (format == 'x')
		len += print_x(va_arg(args, unsigned int));
	else if (format == '%')
		len += print_percent();
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += ft_formats(args, format[i]);
			i++;
		}
		else
		{
			len += write(1, &format[i], 1);
			i++;
		}
	}
	va_end(args);
	return (len);
}

/*#include <stdio.h>
int	main(void)
{
	printf("%c\n", 'c');
	ft_printf("%c", 'c');
	write(1, "\n", 1);

	int	w = 43;
	void	*ptr = &w;
	printf("%p\n", ptr);
	ft_printf("%p", ptr);
	write(1, "\n", 1);

	void *pointr = NULL;
	printf("%p\n", pointr);
	ft_printf("%p\n", pointr);

	char	*s = NULL;
	printf("%s\n", s);
	ft_printf("%s", s);
	write(1, "\n", 1);

	printf("%i\n", -89843);
	ft_printf("%i", -89843);
	write(1, "\n", 1);

	printf("%d\n", 7878);
	ft_printf("%d", 7878);
	write(1, "\n", 1);

	printf("%u\n", 136);
	ft_printf("%u", 136);
	write(1, "\n", 1);

	printf("%x\n", 11136);
	ft_printf("%x", 11136);
	write(1, "\n", 1);

	printf("%X\n", 15154);
	ft_printf("%X", 15154);
	write(1, "\n", 1);
	
	ft_printf("40 is 50%% of 80\n");
	printf("40 is 50%% of 80\n");
	return 0;
}*/
