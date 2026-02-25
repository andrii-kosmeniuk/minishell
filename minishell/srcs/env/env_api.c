/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_api.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:28:11 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/25 14:28:41 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_unset(t_env **head, char *key);
int	env_set(t_env **head, char *key, char *value, bool exported);
bool	env_is_valid_identifier(char *s);
t_env	*env_find(t_env *head, char *key)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

bool	env_is_valid_identifier(char *s)
{
	if (!s || !*s)
		return (false);
	if (!ft_isalpha(*s) && *s != '_' && *s != '.' && *s != ' ')
		return (false);
	s++;
	while (*s)
	{
		if (!alpha_numeric_underscore(*s))
			return (false);
		s++;
	}
	return (true);
}

static int	env_update_node(t_env *node, char *value, bool exported)
{
	char	*new_value;

	if (value)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return (0);
		free(node->value);
		node->value = new_value;
	}
	node->exported = exported;
	return (1);
}

int	env_set(t_env **head, char *key, char *value, bool exported)
{
	t_env	*existing;
	t_env	*new_node;

	existing = env_find(*head, key);
	if (existing)
		return (env_update_node(existing, value, exported));
	new_node = create_node(key, value);
	if (!new_node)
		return (0);
	new_node->exported = exported;
	add_to_list(head, new_node);
	return (1);
}

int	env_unset(t_env **head, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev == NULL)
				*head = cur->next;
			else
				prev->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
