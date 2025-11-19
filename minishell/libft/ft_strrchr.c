/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:07:09 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/24 16:07:10 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	ssize_t	j;

	i = 0;
	while (str[i])
	{
		i++;
	}
	j = (ssize_t)i;
	while (--j >= 0)
	{
		if (str[j] == c)
			return ((char *)&str[j]);
	}
	if (c == '\0')
	{
		return ((char *)&str[i]);
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	const char	*a = "hello a w- how are you doing todaaaay";
	char	b = 'w';

	printf("%s\n", strrchr(a, b));
	printf("%s\n", ft_strrchr(a, b));
	return (0);
}*/
