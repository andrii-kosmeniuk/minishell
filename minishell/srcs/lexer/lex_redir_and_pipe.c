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
		if (!build_list(shell, normal, HERE_DOC, "<<"))
			return (false);
	}
	else
	{
		*len = 1;
		if (!build_list(shell, normal, R_INPUT, "<"))
			return (false);
	}
	return (true);
}

bool	tokenize_output_redirect(const char *input, t_shell *shell, int *len)
{
	if (input[1] == '>')
	{
		*len = 2;
		if (!build_list(shell, normal, R_APPEND, ">>"))
			return (false);
	}
	else
	{
		*len = 1;
		if (!build_list(shell, normal, R_OUTPUT, ">"))
			return (false);
	}
	return (true);
}

bool	tokenize_pipe(const char *input, t_shell *shell, int *len)
{
	if (input[0] == '|')
	{
		*len = 1;
		if (!build_list(shell, normal, PIPE, "|"))
		{
			return (false);
		}
	}
	return (true);
}
