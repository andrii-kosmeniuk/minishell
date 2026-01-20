/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:15:37 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/17 18:24:37 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	env_size(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	add_to_list(t_env **head, t_env *neww)
{
	t_env	*temp;

	if (!head || !neww)
		return ;
	if (*head == NULL)
	{
		*head = neww;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = neww;
}

t_env	*create_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(name);
	if (!new_node->key)
		return (free(new_node), NULL);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (free(new_node->key), free(new_node), NULL);
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}
