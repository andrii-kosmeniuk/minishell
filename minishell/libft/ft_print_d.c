/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:38:20 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/13 19:45:42 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_d(int d)
{
	int		count;
	char	c;

	count = 0;
	if (d == -2147483648)
	{
		count += write(1, "-2147483648", 11);
		return (count);
	}
	if (d < 0)
	{
		count += write(1, "-", 1);
		d = -d;
	}
	if (d >= 10)
	{
		count += print_d(d / 10);
	}
	c = (d % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}
/*
int main(void)
{
	int print_f = printf("%d\n", -53636);
	int my_print = print_d(-53636);
	write(1, "\n", 1);
	printf("length print_f: %d\nprint_d: %d\n", print_f - 1, my_print);
	return 0;
}*/
