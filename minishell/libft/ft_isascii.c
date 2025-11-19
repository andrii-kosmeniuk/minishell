/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:53:54 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/24 12:53:55 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isascii(int d)
{
	if (d >= 0 && d <= 127)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char alpha = 'a';
	char digit = '6';
	unsigned char str = 128;

	printf("%d\n", ft_isascii(alpha));
	printf("%d\n", ft_isascii(digit));
	printf("%d\n", ft_isascii(str));
	return 0;
}*/
