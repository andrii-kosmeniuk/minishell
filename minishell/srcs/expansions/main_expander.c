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

static size_t	t_len(t_shell *shell, char **args, bool *should_expand,
						t_env *env)
{
	size_t	total;
	char	**buffer;
	size_t	j;
	size_t	i;

	total = 0;
	i = 0;
	while (args[i])
	{
		if (should_expand[i])
			buffer = expand_args(shell, &should_expand[i], *args, env);
		else
			buffer = no_expansions(*args);
		if (!buffer)
			return (0);
		j = 0;
		while (buffer[j])
		{
			total++;
			j++;
		}
		free_array(buffer);
		i++;
	}
	return (total);
}

static char	**expand_final_args(t_shell *shell, char **args,
									bool *should_expand, t_env *env)
{
	char	**av;
	size_t	i;
	size_t	j;
	size_t	k;
	char	**buffer;

	av = ft_calloc(t_len(shell, args, should_expand, env) + 1, sizeof(char *));
	if (!av)
		return (NULL);
	i = 0;
	k = 0;
	while (args[i])
	{
		if (should_expand[i])
			buffer = expand_args(shell, &should_expand[i], args[i], env);
		else
			buffer = no_expansions(args[i]);
		if (!buffer)
			return (free_array(av), NULL);
		j = 0;
		while (buffer[j])
		{
			av[k] = ft_strdup(buffer[j]);
			if (!av[k])
				return (free_array(buffer), free_array(av), NULL);
			k++;
			j++;
		}
		free_array(buffer);
		i++;
	}
	av[k] = NULL;
	return (av);
}

bool	expand_all(t_shell *shell, t_cmd *cmd, t_env *env)
{
	t_cmd	*cur;
	char	**expanded;

	cur = cmd;
	while (cur)
	{
		if (!cur->args)
		{
			cur = cur->next;
			continue ;
		}
		expanded = expand_final_args(shell, cur->args, cur->expand, env);
		if (!expanded)
			return (false);
		free_array(cur->args);
		cur->args = expanded;
		cur = cur->next;
	}
	return (true);
}
