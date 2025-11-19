/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:53:18 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/25 17:17:39 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			i;

	str = (unsigned char *)s;
	ch = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char	*str = "aslagifzvipisagz";
	unsigned char	ch = '3';

	char *new = memchr(str, ch, 2);
	if (new)
	{
		printf("%s\n", new);
		printf("%p\n", new);
	}
	else
	{
		printf("%s\n", new);
		printf("%p\n", (void *)new);
	}

	char *result = ft_memchr(str, ch, 2);
	if (result)
	{
		printf("%s\n", result);
		printf("%p\n", result);
	}
	else
	{
		printf("%s\n", result);
		printf("%p\n", (void *)result);
	}
	return (0);
}*/
