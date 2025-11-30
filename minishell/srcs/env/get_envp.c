/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:20:22 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/27 18:19:50 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//this build a linked list full of the key and values of the env variables
//each node has one key and one value (KEY=value), so we loop until = is found,
//all to the left is KEY rest is value
//
//we can also check for duplicates here, if a duplicate variable is found, we 
//keep the last (as per what BASH does)

static void	build_minimum_env(t_shell *shell, t_data *data)
{
	t_env	*node;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	node = create_node("PWD", pwd);
	if (!node)
		return (free(pwd));
	free(pwd);
	add_to_list(&shell->environment_p, node);
	node = create_node("SHLVL", "1");
	if (!node)
		return (free_env_list(shell->environment_p));
	data->shlvl = 1;
	add_to_list(&shell->environment_p, node);
	node = create_node("_", "/usr/bin/env");
	if (!node)
		return (free_env_list(shell->environment_p));
	add_to_list(&shell->environment_p, node);
}

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

static t_env	*empty_env(char **envp, t_shell *shell, t_env **h, t_data *data)
{
	if (!envp || !envp[0])
	{
		build_minimum_env(shell, data);
		shell->environment_p = *h;
		return (*h);
	}
	return (NULL);
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

t_env	*list_key_value(t_shell *shell, t_env **head, char **envp, t_data *data)
{
	char	*key;
	char	*value;
	t_env	*node;
	int		has_equal;

	*head = NULL;
	if (empty_env(envp, shell, head, data) == NULL)
	{
		while (*envp)
		{
			has_equal = assign_key_and_value(*envp, &key, &value);
			if (!key || (!has_equal && !key) || (has_equal && !value))
				return (free(key), free(value), free_env_list(*head), NULL);
			node = create_node(key, value);
			if (!node)
				return (free(key), free(value), free_env_list(*head), NULL);
			replace_key_if_exists(head, key);
			free_key_value(key, value);
			add_to_list(head, node);
			envp++;
		}
	}
	shell->environment_p = *head;
	return (*head);
}

/*int	main(void)
{
	t_env	*head = NULL;
	t_shell	shell;
	char	*fake_envp[] = {
        "USER=mauro",
        "HOME=/home/mauro_42",
        "PATH=/usr/bin:/bin",
        "EMPTY_VALUE=",
        "NOEQUALSIGN",
		"HOME=/home/mauro_forty_two",
        NULL};
	t_env	*result = create_list_key_value(&shell, &head, fake_envp);
	if (!result)
		return (printf("function error\n"), 1);
	print_env_list(head);
	free_env_list(head);
	return (0);
}*/
