/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 23:13:48 by akosmeni          #+#    #+#             */
/*   Updated: 2026/02/26 23:13:56 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_content(t_shell *shell, t_env *env, t_token *cur)
{
	char	*expanded;

	if (!cur->should_expand)
		return (ft_strdup(cur->content));
	expanded = expand_variables(shell, cur->content, env);
	return (expanded);
}

static bool	expand_single_token(t_shell *shell, t_env *env, t_token *cur)
{
	char	*expanded;

	expanded = expand_content(shell, env, cur);
	if (!expanded)
		return (false);
	free(cur->content);
	cur->content = expanded;
	cur->should_expand = false;
	return (true);
}

static bool	merge_two_tokens(t_shell *shell, t_token *cur, t_env *env)
{
	char	*merged;
	char	*cur_content;
	char	*next_content;
	t_token	*next;

	cur_content = expand_content(shell, env, cur);
	next_content = expand_content(shell, env, cur->next);
	if (!cur_content || !next_content)
		return (free(cur_content), free(next_content), false);
	merged = ft_strjoin(cur_content, next_content);
	free(cur_content);
	free(next_content);
	if (!merged)
		return (false);
	free(cur->content);
	cur->content = merged;
	cur->should_expand = false;
	cur->was_merged = true;
	cur->type = WORD;
	next = cur->next;
	cur->next = next->next;
	free(next->content);
	free(next);
	return (true);
}

bool	handle_token_merge(t_shell *shell, t_env *env,
	t_token **cur, t_token **prev)
{
	if (!(*cur)->next || (*cur)->next->has_space_before
		|| (*cur)->next->type == R_INPUT || (*cur)->next->type == R_OUTPUT
		|| (*cur)->next->type == R_APPEND || (*cur)->next->type == HERE_DOC
		|| (*cur)->next->type == PIPE)
	{
		if (!expand_single_token(shell, env, *cur))
			return (false);
		*prev = *cur;
		*cur = (*cur)->next;
	}
	else
	{
		if (!merge_two_tokens(shell, *cur, env))
			return (false);
		*prev = *cur;
	}
	return (true);
}

bool	advance_merger(t_token **cur, t_token **prev)
{
	if ((*cur)->type == R_INPUT || (*cur)->type == R_OUTPUT
		|| (*cur)->type == R_APPEND || (*cur)->type == HERE_DOC
		|| (*cur)->type == PIPE)
	{
		*prev = *cur;
		*cur = (*cur)->next;
		return (true);
	}
	return (false);
}
