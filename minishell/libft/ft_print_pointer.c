/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:18:12 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/13 19:14:57 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hex_x_pointer(unsigned long x)
{
	char	*digits;
	int		count;

	count = 0;
	digits = "0123456789abcdef";
	if (x >= 16)
		count += hex_x_pointer(x / 16);
	count += write(1, &digits[x % 16], 1);
	return (count);
}

int	print_pointer(unsigned long pointer)
{
	int		count;

	count = 0;
	if (pointer == 0)
	{
		count += write(1, "(nil)", 5);
		return (count);
	}
	count += write(1, "0x", 2);
	count += hex_x_pointer(pointer);
	return (count);
}
/*
int	main(void)
{
	unsigned long print_f = printf("%p\n", (void *)00);
	unsigned long my_print = print_pointer(00);
	write(1, "\n", 1);
	printf("length print_f: %lu\nprint_pointer: %lu\n", print_f - 1, my_print);
	return 0;
}*/
