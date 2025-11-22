/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:15:37 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/22 16:15:38 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_list(t_env **head, t_env *new)
{
	t_env	*temp;

	if (!head || !new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

t_env	*create_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = name;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

int	duplicate_variables(t_shell *shell, char **envp, char *previous_variable)
{
	while (*envp)
	{
		if (ft_strcmp(envp[i], previous_variable) == 0)
			return (1);
		envp++;
	}
	return (0);
}
