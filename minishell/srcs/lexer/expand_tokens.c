/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:38:21 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 23:13:39 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	merge_tokens(t_shell *shell, t_token *head, t_env *env)
{
	t_token	*cur;
	t_token	*prev;

	cur = head;
	prev = NULL;
	while (cur)
	{
		if (advance_merge_cursor(&cur, &prev))
			continue ;
		if (!handle_token_merge(shell, env, &cur, &prev))
			return (false);
	}
	return (true);
}
