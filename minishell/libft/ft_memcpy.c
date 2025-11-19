/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:12:11 by milija-h          #+#    #+#             */
/*   Updated: 2025/10/18 16:42:49 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destination;
	const char	*source;
	size_t		i;

	destination = (char *)dest;
	source = (const char *)src;
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}
/*
int	main(void)
{
	char	dest[100] = {};
	char 	source[10] = {0,0,3,5,0};
	char	dest1[100] = {};
	char 	src1[10] = {0,0,3,5,0};


	src1[0] -= 5;
	source[0] -= 5;
	memcpy(dest1, src1, 6);
	ft_memcpy(dest, source, 6);
	ft_putnbr_fd(dest1[0], 1);
	ft_putnbr_fd(dest[0], 1);
	return (0);
}*/
