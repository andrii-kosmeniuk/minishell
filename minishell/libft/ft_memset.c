/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:43:01 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/02 11:49:48 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char			*str;
	unsigned char	a;
	size_t			i;

	str = (char *)s;
	a = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		str[i] = a;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char	letters[100] = "           Filling with * ";
	char	a = '*';

	printf("before:%s\n", letters);
	ft_memset(letters, a, 11);
	printf(" after:%s\n", letters);
	return 0;
}*/
