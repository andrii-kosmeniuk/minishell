/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:09:27 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/04 13:46:02 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redir_pipe(t_shell *shell, const char *input, int *len)
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

static int	quotes(t_shell *shell, const char *input, int *len)
{
	char	quote;

	quote = *input;
	if (shell->state == normal && quote == '\'')
	{
		if (!tokenize_single_quotes(shell, (char *)input, len))
			return (1);
	}
	else if (shell->state == normal && quote == '\"')
	{
		if (!tokenize_double_quotes(shell, (char *)input, len))
			return (1);
	}
	return (0);
}

t_token	*build_token_list(const char *input, t_shell *shell)
{
	int		len;

	len = 0;
	shell->state = normal;
	while (*input)
	{
		while (*input && my_isspace(*input))
			input++;
		if (!*input)
			break ;
		if (*input == '<' || *input == '>' || *input == '|')
			redir_pipe(shell, (char *)input, &len);
		else if (*input == '\'' || *input == '\"')
			shell->redir_error = quotes(shell, (char *)input, &len);
		else if (*input)
		{
			shell->redir_error = tokenize_word((char *)input, shell, &len);
			if (shell->redir_error == 1)
				printf("error here mate\n");
		}
		if (shell->redir_error == 1)
			return (free_tokens(shell->head), shell->head = NULL, NULL);
		input += len;
	}
	return (shell->head);
}
