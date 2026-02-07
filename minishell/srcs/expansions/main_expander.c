/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:47:57 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/07 14:24:02 by milija-h         ###   ########.fr       */
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
			tmp = final_args(cur->content, env, cur->should_expand, exit);
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

static char	**expand_final_args(char **args, t_token *tkn, t_env *env, int exit)
{
	char	**argv;
	char	**buffer;
	size_t	i;
	size_t	j;

	argv = ft_calloc(total_length(tkn, env, exit) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (*args)
	{
		buffer = final_args(*args, env, 1, exit);
		if (!buffer)
			return (free_array(argv), NULL);
		j = 0;
		while (buffer[j])
			argv[i++] = ft_strdup(buffer[j++]);
		free_array(buffer);
		args++;
	}
	argv[i] = NULL;
	return (argv);
}

bool	expand_all(t_cmd *cmd, t_token *tkn, t_env *env, int exit_code)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur)
	{
		cur->args = expand_final_args(cur->args, tkn, env, exit_code);
		if (!cur->args)
			return (false);
		cur = cur->next;
	}
	return (true);
}
