/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:41:33 by milija-h          #+#    #+#             */
/*   Updated: 2025/04/25 19:55:58 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicated;
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
		i++;
	duplicated = (char *)malloc(i + 1);
	if (duplicated == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		duplicated[j] = s[j];
		j++;
	}
	duplicated[j] = '\0';
	return (duplicated);
}

/*#include <bsd/string.h>
#include <stdio.h>
int	main(void)
{
	const char	*src = NULL;
	char	*result = ft_strdup(src);

	printf("%s\n", result);
	free(result);
	return (0);
}*/
