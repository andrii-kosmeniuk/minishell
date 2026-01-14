/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 21:32:43 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/14 21:32:57 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
