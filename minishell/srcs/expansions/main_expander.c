/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:47:57 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/16 19:48:10 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	total_length(t_token *token, t_env *env, int exit)
{
	char	**tmp;
	size_t	j;
	size_t	count;
	t_token	*cur;

	count = 0;
	cur = token;
	while (cur)
	{
		if (cur->type == WORD || cur->type == S_QUOTE || cur->type == D_QUOTE)
		{
			tmp = final_args(cur->content, cur->should_expand, env, exit);
			if (!tmp)
				return (0);
			j = 0;
			while (tmp[j])
			{
				count++;
				j++;
			}
			free_array(tmp);
		}
		cur = cur->next;
	}
	return (count);
}

char	**expand_final_args(t_token *tokens, t_env *env, int exit)
{
	char	**argv;
	char	**buffer;
	size_t	j;
	size_t	i;
	t_token	*cur;

	argv = ft_calloc(total_length(tokens, env, exit) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	buffer = NULL;
	i = 0;
	cur = tokens;
	while (cur)
	{
		if (cur->type == WORD || cur->type == S_QUOTE || cur->type == D_QUOTE)
		{
			buffer = final_args(cur->content, cur->should_expand, env, exit);
			if (!buffer)
				return (free_array(argv), NULL);
			j = 0;
			while (buffer[j])
			{
				argv[i] = ft_strdup(buffer[j]);
				if (!argv[i])
					return (free_array(buffer), free_array(argv), NULL);
				i++;
				j++;
			}
			free_array(buffer);
		}
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}
