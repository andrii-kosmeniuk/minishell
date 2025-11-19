/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_X.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:03:40 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/13 19:49:32 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	my_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	x_len(unsigned int num)
{
	int	len;

	len = 0;
	if (num == 0)
		len = 1;
	while (num != 0)
	{
		len ++;
		num = num / 16;
	}
	return (len);
}

char	*hex_to_string(unsigned int x)
{
	char	*digits;
	char	*hexa;
	int		i;

	i = x_len(x);
	digits = "0123456789ABCDEF";
	hexa = (char *)malloc(i + 1);
	if (hexa == NULL)
		return (NULL);
	hexa[i] = '\0';
	i = x_len(x) - 1;
	while (x > 0)
	{
		hexa[i] = digits[x % 16];
		x = x / 16;
		i--;
	}
	return (hexa);
}

int	print_x_upper(unsigned int num)
{
	char	*hex_string;

	if (num == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	hex_string = hex_to_string(num);
	if (hex_string != NULL)
	{
		write(1, hex_string, my_strlen(hex_string));
		free(hex_string);
	}
	return (x_len(num));
}
/*
int	main(void)
{
	unsigned int print_f = printf("%x\n", 456);
	unsigned int my_print = print_x_upper(456);
	write(1, "\n", 1);
	printf("length of print_f: %d, my_print: %d\n", print_f -1, my_print);
	return 0;
}*/
