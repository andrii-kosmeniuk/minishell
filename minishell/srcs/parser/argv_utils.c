/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:46:51 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/18 15:47:35 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	count_words(char **array)
{
	size_t	count;

	count = 0;
	while (array[count])
		count++;
	return (count);
}

static	char **single_array(char *content)
{
	char	**words;

	words = ft_calloc(2, sizeof(char *));
	if (!words)
		return (NULL);
	words[0] = ft_strdup(content);
	if (!words[0])
		return (free(words), NULL);
	words[1] = NULL;
	return (words);
}

static	char **store_words(t_token *cur)
{
	if (cur->type == WORD && !cur->was_merged)
		return (ft_split(cur->content, ' '));
	else
		return (single_array(cur->content));
}

static	char	**merge_args(char **old_args, int old_count, char **words,
							int word_count)
{
	char	**new_args;
	int		i;
	int		j;

	new_args = ft_calloc(old_count + word_count + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < old_count)
	{
		new_args[i] = old_args[i];
		i++;
	}
	j = 0;
	while (j < word_count)
	{
		new_args[i] = ft_strdup(words[j]);
		if (!new_args[i])
			return (free_partial(new_args, i), NULL);
		i++;
		j++;
	}
	new_args[i] = NULL;
	return (new_args);
}

t_cmd	*add_args(t_cmd *cmd, t_token *token)
{
	char	**words;
	char	**new_args;
	int		count;

	if (!cmd || !token || !token->content)
		return (NULL);
	words = store_words(token);
	if (!words)
		return (NULL);
	count = count_words(words);
	new_args = merge_args(cmd->args, cmd->argc, words, count);
	free_array(words);
	if (!new_args)
		return (NULL);
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	cmd->argc += count;
	return (cmd);
}
