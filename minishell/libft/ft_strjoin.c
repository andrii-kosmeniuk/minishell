/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:03:08 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/27 09:28:07 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static char	*ft_edge_cases_join(char const *s1, char const *s2)
{
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	s3 = ft_edge_cases_join(s1, s2);
	return (s3);
	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}*/

static char	*check(char const *s1, char const *s2)
{
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*check_str;
	char		*res;
	size_t		len1;
	size_t		len2;

	if (!s1 && !s2)
		return (NULL);
	check_str = check(s1, s2);
	if (check_str)
		return (check_str);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc((sizeof(char) * (len1 + len2)) + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}
/*#include <stdio.h>
int	main(void)
{
	char const	*s1 = NULL;
	char const	*s2 = NULL;

	char	*s3 = ft_strjoin(s1, s2);
	printf("s1 = %s\n", s1);
	printf("s2 = %s\n", s2);
	printf("s3 = %s\n", s3);
	return (0);
}*/