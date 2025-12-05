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

void	redir_pipe(t_shell *shell, t_token *token, const char *input, int *len)
{
	char	redir;

	redir = *input;
	if (redir == '>')
	{
		if (!tokenize_output_redirect((char *)input, shell, len))
			return (free_all(token, shell));
	}
	else if (redir == '>')
	{
		if (!tokenize_input_redirect((char *)input, shell, len))
			return (free_all(token, shell));
	}
	else
	{
		if (!tokenize_pipe((char *)input, shell, len))
			return (free_all(token, shell));
	}
}

void	quotes(t_shell *shell, t_token *token, const char *input, int *len)
{
	char	quote;

	quote = *input;
	if (quote == '\'')
	{
		if (!tokenize_single_quotes(shell, (char *)input, len))
			return (free_all(token, shell));
	}
	else
	{
		if (!tokenize_double_quotes(shell, (char *)input, len))
			return (free_all(token, shell));
	}
}

t_token	*build_token_list(t_token *token, const char *input, t_shell *shell)
{
	int		len;

	len = 0;
	while (*input)
	{
		skip_white_spaces(input);
		if (*input == '<' || *input == '>' || *input == '|')
		{
			redir_pipe(shell, token, (char *)input, &len);
			input += len;
		}
		else if (*input == '\'' || *input == '\'')
		{
			quotes(shell, token, (char *)input, &len);
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
