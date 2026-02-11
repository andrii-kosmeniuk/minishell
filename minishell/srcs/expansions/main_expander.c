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

static size_t	total_length(char **args, t_env *env)
{
	char	**tmp;
	size_t	j;
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (args[i])
	{
		tmp = final_args(args[i], env, true);
		if (!tmp)
			return (0);
		j = 0;
		while (tmp[j])
		{
			count++;
			j++;
		}
		free_array(tmp);
		i++;
	}
	return (count);
}

static char	**expand_final_args(char **args, t_env *env)
{
	char	**argv;
	char	**buffer;
	size_t	i;
	size_t	j;

	argv = ft_calloc(total_length(args, env) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (*args)
	{
		buffer = final_args(*args, env, 1);
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

bool	expand_all(t_cmd *cmd, t_env *env)
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
		expanded = expand_final_args(cur->args, env);
		if (!expanded)
			return (false);
		free_array(cur->args);
		cur->args = expanded;
		cur = cur->next;
	}
	return (true);
}
