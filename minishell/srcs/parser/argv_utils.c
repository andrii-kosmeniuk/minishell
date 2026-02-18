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

static char	**single_array(char *content)
{
	char	**words;

	words = ft_calloc(2, sizeof(char *));
	if (!words)
		return (NULL);
	words[0] = content;
	words[1] = NULL;
	return (words);
}

static char	**store_words(t_token *cur)
{
	char	**words;

	if (cur->type == WORD)
		return (ft_split(cur->content, ' '));
	else
	{
		words = single_array(ft_strdup(cur->content));
		if (!words)
			return (NULL);
	}
	return (words);
}

t_cmd	*add_args(t_cmd *cmd, t_token *token)
{
	char	**cmd_args;
	char	**words;
	size_t	count;
	int		i;
	int		j;

	if (!cmd || !token || !token->content)
		return (NULL);
	words = store_words(token);
	if (!words)
		return (NULL);
	count = count_words(words);
	cmd_args = ft_calloc((count + cmd->argc + 1), sizeof(char *));
	if (!cmd_args)
		return (free_array(words), NULL);
	i = 0;
	while (i < cmd->argc)
	{
		cmd_args[i] = cmd->args[i];
		i++;
	}
	j = 0;
	while (words[j])
	{
		cmd_args[i] = ft_strdup(words[j]);
		if (!cmd_args[i])
			return (free_array(words), free_partial(cmd_args, i), NULL);
		i++;
		j++;
	}
	cmd_args[i] = NULL;
	free_array(words);
	if (cmd->args)
		free(cmd->args);
	cmd->args = cmd_args;
	cmd->argc += count;
	return (cmd);
}
