/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:51:43 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/11 18:51:45 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**grow_words(char **old, int count)
{
	char	**new_;
	int		i;

	new_ = ft_calloc((count + 2), sizeof(char *));
	if (!new_)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_[i] = old[i];
		i++;
	}
	new_[count] = NULL;
	new_[count + 1] = NULL;
	free(old);
	return (new_);
}

static char	**word_splitting(char *expanded_string)
{
	char	**words;
	char	*word;
	char	*start;
	int		word_count;

	words = NULL;
	word_count = 0;
	while (*expanded_string)
	{
		while (*expanded_string && my_isspace(*expanded_string))
			expanded_string++;
		if (*expanded_string == '\0')
			break ; //if only string is only space
		start = expanded_string; // keep track of word_start
		while (*expanded_string && !my_isspace(*expanded_string))
			expanded_string++;
		word = ft_substr(start, 0, expanded_string - start);
		if (!word)
			return (NULL);
		words = grow_words(words, word_count);
		if (!words)
			return (free(word), NULL);
		words[word_count] = word;
		word_count++;
	}
	return (words);
}

char	**final_expand(char *input, t_env *env)
{
	char	**expanded;
	char	**argv;

	expanded = expand(input, env);
	if (!expanded)
		return (NULL);
	argv = word_splitting(expanded);
	if (!argv)
		return (free_array(expanded), NULL);
	free_array(expanded);
	return (argv);
}
