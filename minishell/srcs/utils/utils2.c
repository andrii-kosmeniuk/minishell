/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:34:49 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/12 22:35:16 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_argument(t_token *token)
{
	if (token->type == WORD || token->type == EXPAND || token->type == S_QUOTE
		|| token->type == D_QUOTE)
		return (true);
	return (false);
}

bool	is_redirection(t_token *token)
{
	if (token->type = R_INPUT || token->type == R_OUTPUT
		|| token->type == R_APPEND || token->type == HERE_DOC)
		return (true);
	return (false);
}
