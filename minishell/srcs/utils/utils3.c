/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:00:42 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/17 18:28:51 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h>

int	alpha_numeric_underscore(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || (c == '_'))
		return (1);
	else
		return (0);
}

void	determine_state(t_state state, char *input)
{
	if (state == normal && *input == '\'')
		state = single_q;
	else if (state == normal && *input == '"')
		state = double_q;
	else if (state == single_q && *input == '\'')
		state = normal;
	else if (state == double_q && *input == '"')
		state = normal;
}

bool	is_single_word(char *expanded)
{
	while (*expanded)
	{
		if (my_isspace(*expanded))
			return (false);
		expanded++;
	}
	return (true);
}

bool	is_word_quoted(t_token *token)
{
	if (token->type == WORD || token->type == S_QUOTE || token->type == D_QUOTE)
		return (false);
	return (true);
}
