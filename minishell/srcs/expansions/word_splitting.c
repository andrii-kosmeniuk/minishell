/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 21:32:43 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/16 21:24:35 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*static int	count_words(char *input)
{
	int	count;

	count = 0;
	while (*input)
	{
		while (*input && my_isspace(*input))
			input++;
		if (*input)
			count++;
		while (*input && !my_isspace(*input))
			input++;
	}
	return (count);
}

char	**word_split(char *expanded)
{
	char	**words;
	char	*start;
	int		i;

	words = ft_calloc(count_words(expanded) + 1, sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	while (*expanded)
	{
		while (*expanded && my_isspace(*expanded))
			expanded++;
		if (!*expanded)
			break ;
		start = expanded;
		while (*expanded && my_isspace(*expanded))
			expanded++;
		words[i] = ft_substr(start, 0, expanded - start);
		if (!words[i])
			return (free_array(words), NULL);
		i++;
	}
	words[i] = NULL;
	return (words);
}*/
