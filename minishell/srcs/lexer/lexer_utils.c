/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:52:53 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/15 18:47:23 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_token(char *content, t_state state, t_type type,
						bool should_expand)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	if (!token->content)
		return (free(token), NULL);
	token->state = state;
	token->type = type;
	token->should_expand = should_expand;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*cur;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
	}
}

t_token	*build_list(t_shell *shell, t_type type, char *value,
				bool should_expand)
{
	t_token	*t_node;

	t_node = create_token(value, shell->state, type, should_expand);
	if (!t_node)
		return (NULL);
	add_token(&shell->head, t_node);
	return (shell->head);
}
