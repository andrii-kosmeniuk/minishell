/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:35:04 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/11 17:35:05 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	x_leng(unsigned int num)
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

void	hex_x(unsigned int x)
{
	char	*digits;

	digits = "0123456789abcdef";
	if (x >= 16)
		hex_x(x / 16);
	write(1, &digits[x % 16], 1);
}

int	print_x(unsigned int num)
{
	if (num == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	hex_x(num);
	return (x_leng(num));
}
/*
int	main(void)
{
	unsigned int print_f = printf("%x\n", 45556);
	unsigned int my_print = print_x(45556);
	write(1, "\n", 1);
	printf("length of print_f: %d, my_print: %d\n", print_f -1, my_print);
	return 0;
}*/
