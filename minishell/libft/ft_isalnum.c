/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:58:18 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/24 12:58:20 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char alpha = 'a';
	char digit = '2';
	char none = '?';

	printf("%d\n", ft_isalnum(alpha));
	printf("%d\n", ft_isalnum(digit));
	printf("%d\n", ft_isalnum(none));
	return 0;
}*/
