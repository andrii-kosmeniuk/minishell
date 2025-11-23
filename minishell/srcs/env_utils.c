/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:14:16 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/22 22:14:17 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//still add check for when SHLVL exists
////maybe manually insert =
void	build_minimum_env(t_shell *shell, char **envp)
{
	char	*cur_dir;
	char	*value;
	t_env	*node;
	char	*key;

	while (*envp)
	{
		if (ft_strcmp(*envp, "PWD") != 0)
		{
			key = "PWD";
			cur_dir = getcwd(NULL, 0);
			if (!cur_dir)
				return ; //remember to free later
			node = create_node(key, cur_dir);
			if (!node)
				return (free(cur_dir));
		}
		if (ft_strcmp(*envp, "SHLVL") != 0)
		{
			key = "SHLVL";
			value = "1";
			node = create_node(key, value);
			if (!node)
				return (free(cur_dir));
			add_to_list(head, node);
		}
		if (ft_strcmp(*envp, "_") != 0)
		{
			key = "_";
			value = "/usr/bin/env";//maybe trace in history last used commands and use it
		}
	}
}
