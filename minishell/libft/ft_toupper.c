/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:45:46 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/24 12:45:48 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(unsigned int ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		ch -= 32;
	}
	return (ch);
}
/*
int	main(void)
{
	char a = 'a';
	char b = 'A';
	char c = '!';

	printf("%c\n", ft_toupper(a));
	printf("%c\n", ft_toupper(b));
	printf("%c\n", ft_toupper(c));
	return 0;
}*/
