/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:41:47 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/13 11:43:46 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value(t_env *env, char *variable_name)
{
	t_env	*cur;
	char	*value;

	cur = env;
	value = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, variable_name) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL)
}

bool	is_single_word(char *expanded)
{
	while (*expanded)
	{
		if (my_isspace(*expanded))
			return (true);
	}
	return (false);
}

char	*read_variable_name(char *input, char *start_of_variable)
{
	size_t	length;
	char	*variable_name;

	input = start_of_variable;
	if (!is_valid(*input))
		return (NULL);
	while (alpha_numeric_underscore(*input))
		input++;
	length = input - start_of_variable;
	variable_name = substring(input, start_of_variable, length);
	if (!variable_name)
		return (NULL);
	return (variable_name);
}

char	**word_split(char *expanded)
{
	char	**words;
	char	*word;
	char	*start;

	words = NULL;
	word_count = 0;
	while (*expanded)
	{
		while (*expanded && my_isspace(*expanded))
			expanded++;
		if (*expanded == '\0')
			break ; //if string is only space
		start = expanded; // keep track of word_start
		while (*expanded && !my_isspace(*expanded))
			expanded++; // at the end of the word
		word = ft_calloc(expanded - start + 1, sizeof(char))
		if (!word)
			return (free_array(words), NULL);
		*words = ft_calloc(ft_strlen(word) + 1, sizeof(char)); //individual alloc
		if (!(*words)) 
			return (free(word), free_array(words), NULL);
		ft_memcpy(*words, word, ft_strlen(word)); // copy word into *words
		free(word);
		word = NULL;
		words++;
		expanded++;
	}
	return (words);
}
