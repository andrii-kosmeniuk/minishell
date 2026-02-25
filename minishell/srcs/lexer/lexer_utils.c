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

char	*expand_variables(t_shell *shell, char *input, t_env *env)
{
	t_expand	p;

	p.output = NULL;
	p.len = 0;
	p.exit_code = 0;
	p.env = env;
	while (*input)
	{
		if (*input == '$')
		{
			if (!handle_expansions(&input, &p, shell))
				return (free(p.output), NULL);
			continue ;
		}
		if (!append_char(&p.output, &p.len, *input))
			return (free(p.output), NULL);
		input++;
	}
	if (!p.output)
		return (ft_strdup(""));
	return (p.output);
}

t_token	*create_token(t_type type, char *content, bool should_expand,
						bool has_space_before)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	if (!new_token->content)
		return (free(new_token), NULL);
	new_token->type = type;
	new_token->should_expand = should_expand;
	new_token->has_space_before = has_space_before;
	new_token->was_merged = false;
	new_token->next = NULL;
	return (new_token);
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

	t_node = create_token(type, value, should_expand, shell->had_space);
	if (!t_node)
		return (NULL);
	add_token(&shell->head, t_node);
	return (shell->head);
}
