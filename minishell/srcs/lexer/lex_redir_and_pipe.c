/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redir_and_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:04:56 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/03 22:31:05 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	tokenize_input_redirect(const char *input, t_shell *shell, int *len)
{
	if (input[1] == '<')
	{
		*len = 2;
		if (is_operator(input[2]) || !build_list(shell, HERE_DOC, "<<", false))
			return (false);
	}
	else
	{
		*len = 1;
		if (!build_list(shell, R_INPUT, "<", false))
			return (false);
	}
	return (true);
}

bool	tokenize_output_redirect(const char *input, t_shell *shell, int *len)
{
	if (input[1] == '>')
	{
		*len = 2;
		if (is_operator(input[2]) || !build_list(shell, R_APPEND, ">>", false))
			return (false);
	}
	else
	{
		*len = 1;
		if (!build_list(shell, R_OUTPUT, ">", false))
			return (false);
	}
	return (true);
}

bool	tokenize_pipe(const char *input, t_shell *shell, int *len)
{
	if (input[0] == '|')
	{
		*len = 1;
		if (is_operator(input[1]) || !build_list(shell, PIPE, "|", false))
		{
			shell->redir_error = 1;
			return (false);
		}
	}
	return (true);
}
