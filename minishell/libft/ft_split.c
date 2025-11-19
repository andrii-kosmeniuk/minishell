/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:24:23 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/09 09:00:07 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbr_of_words(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static char	*add_words(const char *str, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	if (!str || end < start)
		return (NULL);
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

void	free_partial(char **array, size_t count)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (i < count)
	{
		free(array[i]);
		i++;
	}
	free (array);
}

static int	ft_fill_array(char **array, const char *s, char c)
{
	t_var	p;

	p.i = 0;
	p.j = 0;
	while (s[p.i])
	{
		while (s[p.i] && s[p.i] == c)
			p.i++;
		p.start = p.i;
		while (s[p.i] && s[p.i] != c)
			p.i++;
		if (p.i > p.start)
		{
			array[p.j] = add_words(s, p.start, p.i);
			if (!array[p.j])
				return (0);
			p.j++;
		}
	}
	array[p.j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**array;
	size_t		words;

	if (!s)
		return (NULL);
	words = ft_nbr_of_words(s, c);
	array = (char **)malloc((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (!ft_fill_array(array, s, c))
		return (free_partial(array, ft_nbr_of_words(s, c)), NULL);
	return (array);
}

/*#include <stdio.h>
int	main(void)
{
	char const	*str = "Ma, Makldhi, Maödhöguö, Mdöfjlhfudhga, Ma, ";
	char		c = ',';
	char		**arr = ft_split(str, c);
	int			i = 0;

	if (arr == NULL)
	{
		printf("failed malloc");
		return (1);
	}
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}*/
