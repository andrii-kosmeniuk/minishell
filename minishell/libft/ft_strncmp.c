/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:34:48 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/07 12:37:09 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t					i;
	const unsigned char		*s1;
	const unsigned char		*s2;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	i = 0;
	while (i < n && (s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
	{
		return (s1[i] - s2[i]);
	}
	return (0);
}
/*
int	main(void)
{
	const char	*hello = "hello\200";
	const char	*hellO = "hello\0";

	printf("%d\n", ft_strncmp(hello, hellO, 6));
	size_t p = strncmp(hello, hellO, 6);
	printf("%zu\n", p);
	return 0;
}*/
