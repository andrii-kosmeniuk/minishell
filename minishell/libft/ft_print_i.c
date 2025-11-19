/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:19:36 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/13 19:47:27 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_i(int i)
{
	int		count;
	char	c;

	count = 0;
	if (i == -2147483648)
	{
		count += write(1, "-2147483648", 11);
		return (count);
	}
	if (i < 0)
	{
		count += write(1, "-", 1);
		i = -i;
	}
	if (i >= 10)
	{
		count += print_i(i / 10);
	}
	c = (i % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}
/*
int main(void)
{
	int print_f = printf("%i\n", -53636);
	int my_print = print_i(-53636);
	write(1, "\n", 1);
	printf("length print_f: %i\nprint_d: %i\n", print_f - 1, my_print);
	return 0;
}*/
