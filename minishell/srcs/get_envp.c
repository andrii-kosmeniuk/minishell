/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:20:22 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/20 20:20:24 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	create_list_key_value(t_shell *shell, t_env **head, char **envp)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*node;

	if (envp == NULL)
		build_minimum_env(shell);
	while (*envp)
	{
		equal_sign = ft_strchr((*envp, '='));
		if (!equal_sign)
		{
			envp++;
			continue ;
		}
		key = ft_strdup(equal_sign + 1);
		if (!key)
			return ;
		value = ft_strndup(*envp, equal_sign - *envp);
		if (!value)
			return (free(key));
		node = create_node(key, value);
		if (!node)
			return (free(value), free(key));
		add_to_list(head, node);
		envp++;
	}
	shell->environment_p = *head;
}
