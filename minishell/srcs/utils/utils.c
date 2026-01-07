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

bool	syntax_check(t_shell *shell)
{
	t_token	*cur;
	t_token	*next;

	cur = shell->head;
	if (cur->type == PIPE)
		return (fprintf(stderr, PIPE_FIRST), false);
	while (cur)
	{
		next = cur->next;
		if (cur->type == PIPE && next == NULL)
			return (printf(PIPE_END), false);
		if ((cur->type == R_OUTPUT || cur->type == R_INPUT
				|| cur->type == HERE_DOC || cur->type == R_APPEND)
			&& (next && next->type == PIPE))
			return (printf(REDIR_PIPE), false);
		if ((cur->type == R_INPUT || cur->type == R_OUTPUT
				|| cur->type == R_APPEND || cur->type == HERE_DOC)
			&& (next == NULL
				|| next-> type != WORD))
			return (printf(NO_TARGET), false);
		cur = next;
	}
	return (true);
}
