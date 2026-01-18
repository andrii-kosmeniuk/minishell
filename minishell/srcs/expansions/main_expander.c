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

static size_t	total_length(char **args, t_state state, t_env *env, int exit)
{
	char	**tmp;
	size_t	j;
	size_t	count;

	count = 0;
	while (*args)
	{
		tmp = final_args(*args, state, env, exit);
		if (!tmp)
			return (0);
		j = 0;
		while (tmp[j])
		{
			count++;
			j++;
		}
		free_array(tmp);
		args++;
	}
	return (count);
}

char	**expand_final_args(char **args, t_state state, t_env *env, int exit)
{
	char	**argv;
	char	**buffer;
	size_t	j;
	size_t	i;

	argv = ft_calloc(total_length(args, state, env, exit) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	buffer = NULL;
	i = 0;
	while (*args)
	{
		buffer = final_args(*args, state, env, exit);
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
		args++;
	}
	argv[i] = NULL;
	return (argv);
}
