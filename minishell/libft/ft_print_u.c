/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:32:41 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/13 19:46:27 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_u(unsigned int u)
{
	int		count;
	char	c;

	count = 0;
	if (u >= 10)
	{
		count += print_u(u / 10);
	}
	c = (u % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}
/*
int main(void)
{
	unsigned int print_f = printf("%u\n", 453636);
	unsigned int my_print = print_u(453636);
	write(1, "\n", 1);
	printf("length print_f: %u\nprint_d: %u\n", print_f - 1, my_print);
	return 0;	
}*/
