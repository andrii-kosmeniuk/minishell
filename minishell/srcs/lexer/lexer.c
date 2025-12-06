/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:09:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/05 14:54:46 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_pipe(t_shell *shell, const char *input, int *len)
{
	char	redir;

	redir = *input;
	if (redir == '>')
	{
		if (!tokenize_output_redirect((char *)input, shell, len))
		{
			shell->redir_error = 1;
			return ;
		}
	}
	else if (redir == '<')
	{
		if (!tokenize_input_redirect((char *)input, shell, len))
		{
			shell->redir_error = 1;
			return ;
		}
	}
	else if (redir == '|')
	{
		if (!tokenize_pipe((char *)input, shell, len))
			return ;
	}
}

void	quotes(t_shell *shell, const char *input, int *len)
{
	char	quote;

	quote = *input;
	if (quote == '\'')
	{
		if (!tokenize_single_quotes(shell, (char *)input, len))
			return ;
	}
	else if (quote == '\"')
	{
		if (!tokenize_double_quotes(shell, (char *)input, len))
			return ;
	}
}

t_token	*build_token_list(const char *input, t_shell *shell)
{
	int		len;

	len = 0;
	while (*input)
	{
		while (*input && my_isspace(*input))
			input++;
		if (*input == '<' || *input == '>' || *input == '|')
		{
			redir_pipe(shell, (char *)input, &len);
			input += len;
		}
		else if (*input == '\'' || *input == '\"')
		{
			quotes(shell, (char *)input, &len);
			input += len;
		}
		else
		{
			tokenize_word((char *)input, shell, &len);
			input += len;
		}
	}
	return (shell->head);
}
