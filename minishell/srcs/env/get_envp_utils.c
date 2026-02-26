/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 22:50:07 by akosmeni          #+#    #+#             */
/*   Updated: 2026/02/26 22:55:16 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	replace_key_if_exists(t_env **head, char *key)
{
	t_env	*cur_node;
	t_env	*prev;

	cur_node = *head;
	prev = NULL;
	while (cur_node)
	{
		if (!cur_node->key)
			printf("ERROR: cur_node->key is NULL!!\n");
		else if (ft_strcmp(cur_node->key, key) == 0)
		{
			if (prev == NULL)
				*head = cur_node->next;
			else
				prev->next = cur_node->next;
			free(cur_node->key);
			free(cur_node->value);
			free(cur_node);
			return ;
		}
		prev = cur_node;
		cur_node = cur_node->next;
	}
}

static int	assign_key_and_value(char *entry, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(entry, '=');
	if (equal)
	{
		*key = ft_strndup(entry, equal - entry);
		*value = ft_strdup(equal + 1);
		return (1);
	}
	else
	{
		*key = ft_strdup(entry);
		*value = NULL;
		return (0);
	}
}

t_env	*build_from_envp(t_shell *shell, char **envp)
{
	char	*key;
	char	*value;
	t_env	*node;
	int		has_equal;

	while (*envp)
	{
		has_equal = assign_key_and_value(*envp, &key, &value);
		if (!key || (!has_equal && !key) || (has_equal && !value))
			return (free(key), free(value),
				free_env_list(&shell->environment_p), NULL);
		node = create_node(key, value);
		if (!node)
			return (free(key), free(value),
				free_env_list(&shell->environment_p), NULL);
		node->exported = true;
		replace_key_if_exists(&shell->environment_p, key);
		free_key_value(key, value);
		add_to_list(&shell->environment_p, node);
		envp++;
	}
	return (shell->environment_p);
}
