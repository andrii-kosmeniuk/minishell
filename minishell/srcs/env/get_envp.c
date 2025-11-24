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
#include "../../minishell.h"

static void	build_minimum_env(t_shell *shell)
{
	t_env	*node;
	t_env	*node2;
	t_env	*node3;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	node = create_node("PWD", pwd);
	if (!node)
		return (free(pwd));
	add_to_list(&shell->environment_p, node);
	node2 = create_node("SHLVL", "1");
	if (!node2)
		return (free(node));
	add_to_list(&shell->environment_p, node2);
	node3 = create_node("_", "/usr/bin/env");
	if (!node3)
		return (free(node3), free(node2));
	add_to_list(&shell->environment_p, node3);
}

// here we look for an already existing key
// if the key in question already exist we must get rid of it
// we check if the key is in the first node or not and free node
// accordingly
static void replace_key_if_exists(t_env **head, char *key)
{
	t_env	*cur_node;
	t_env	*prev;

	cur_node = *head;
	prev = NULL;
	while (cur_node)
	{
		if (ft_strcmp(cur_node->key, key) == 0)
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

//this build a linked list full of the key and values of the env variables
//each node has one key and one value (KEY=value), so we loop until = is found,
//all to the left is KEY rest is value
//
//we can also check for duplicates here, if a duplicate variable is found, we 
//keep the last (as per what BASH does)

t_env	*create_list_key_value(t_shell *shell, t_env **head, char **envp)
{
	char	*equal;
	char	*key;
	char	*value;
	t_env	*node;

	if (!envp || !envp[0])
	{
		build_minimum_env(shell);
		shell->environment_p = *head;
		return (*head);
	}
	while (*envp)
	{
		equal = ft_strchr(*envp, '=');
		if (equal)
		{
			key = ft_strndup(*envp, equal - *envp);
			value = ft_strdup(equal + 1);
		}
		else
		{
			key = ft_strdup(*envp);
			value = NULL;
		}
		if (!key || (!equal && !key) || (equal && !value))
			return (free(key), free(value), free_env_list(*head), NULL);
		replace_key_if_exists(head, key);
		node = create_node(key, value);
		if (!node)
			return (free(key), free(value), free_env_list(*head), NULL);
		add_to_list(head, node);
		envp++;
	}
	shell->environment_p = *head;
	return (*head);
}
