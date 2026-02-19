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

static bool	redir_pipe(t_shell *shell, char *input, int *len)
{
	char	redir;

	redir = *input;
	if (redir == '>')
	{
		if (!tokenize_output_redirect(input, shell, len))
			return (1);
	}
	else if (redir == '<')
	{
		if (!tokenize_input_redirect(input, shell, len))
			return (1);
	}
	else if (redir == '|')
	{
		if (!tokenize_pipe(input, shell, len))
			return (1);
	}
	return (0);
}

static int	quotes(t_shell *shell, char *input, int *len)
{
	char	quote;

	quote = *input;
	if (shell->state == normal && quote == '\'')
	{
		if (!tokenize_single_quotes(shell, input, len))
			return (1);
	}
	else if (shell->state == normal && quote == '\"')
	{
		if (!tokenize_double_quotes(shell, input, len))
			return (1);
	}
	return (0);
}

static int	tokenize_all(t_shell *shell, char *input, int *len)
{
	if (*input == '<' || *input == '>' || *input == '|')
	{
		if (redir_pipe(shell, input, len) == 1)
			return (1);
	}
	else if (*input == '\'' || *input == '\"')
	{
		if (quotes(shell, input, len) == 1)
			return (1);
	}
	else if (*input)
	{
		if (tokenize_word(input, shell, len) == 1)
			return (1);
	}
	return (0);
}

t_token	*build_token_list(char *input, t_shell *shell)
{
	int		len;

	len = 0;
	shell->state = normal;
	shell->had_space = true;
	shell->redir_error = 0;
	while (*input)
	{
		shell->had_space = false;
		while (*input && my_isspace(*input))
		{
			input++;
			shell->had_space = true;
		}
		if (!*input)
			break ;
		shell->redir_error = tokenize_all(shell, input, &len);
		if (shell->redir_error == 1)
			return (free_tokens(shell->head), shell->head = NULL, NULL);
		input += len;
	}
	if (!merge_tokens(shell, shell->head, shell->environment_p))
		return (free_tokens(shell->head), NULL);
	return (shell->head);
}
