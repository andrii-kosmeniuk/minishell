/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:52:53 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/01 22:34:30 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_token(char *content, t_state state, t_type type)
{
	int		token_len;
	t_token	*token;

	token_len = ft_strlen(content);
	token = malloc(sizeof(t_token) * token_len);
	if (!token)
		return (NULL);
	token->content = content;
	token->state = state;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*cur;

	if (!head || !*head)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	else
	{
		cur = *head;
		while (cur)
			cur = cur->next;
		cur->next = new_token;
	}
}

int	is_operator(char operator)
{
	if (operator == '\'' || operator == '\"' || operator == '<'
		|| operator == '>' || operator == '|')
		return (1);
	return (0);
}
