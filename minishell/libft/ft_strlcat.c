/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:37:35 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/24 12:37:37 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	w;

	i = 0;
	while (dest[i] && i < size)
		i++;
	j = 0;
	while (src[j])
		j++;
	if (size <= i)
		return (size + j);
	w = 0;
	while (src[w] && (i + w < size - 1))
	{
		dest[i + w] = src[w];
		w++;
	}
	dest[i + w] = '\0';
	return (i + j);
}
/*
int	main(void)
{
	const char *src = "fdd";
	char dest[100] = " ";
	size_t length = ft_strlcat(dest, src, 7);
	printf("%s\n", dest);
	printf("%zu\n", length);
	return (0);
}*/
