/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:53:37 by milija-h          #+#    #+#             */
/*   Updated: 2025/05/02 12:00:13 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_is_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			i;
	size_t			j;
	size_t			w;
	char			*new;
	size_t			len_new;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && ft_is_set(s1[i], set))
		i++;
	j = ft_strlen(s1);
	while (j > i && ft_is_set(s1[j - 1], set))
		j--;
	len_new = j - i;
	new = (char *)malloc(len_new + 2);
	if (new == NULL)
		return (NULL);
	w = 0;
	while (i < j)
		new[w++] = s1[i++];
	new[w] = '\0';
	return (new);
}

/*#include <stdio.h>
int	main(void)
{
	char	*s1 = ft_calloc(2147483650, 1);
	ft_memset(s1, 'a', 2147483649);
	char	*set = "a";
	char	*result = ft_strtrim(s1, set);
	printf("%s\n", result);
	free(result);
	return (0);
}*/
