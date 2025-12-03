/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:09:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/03 22:30:19 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*build_token_list(t_token *token, const char *input, t_shell *shell)
{
	int	len;

	len = 0;
	while (*input)
	{
		while (*input < 33)
			input++;
		if (*input == '<')
		{
			if (!tokenize_input_redirect((char *)input, shell, len))
				return (free_all(token, shell), NULL);
			input += len;
		}
		else if (*input == '>')
		{
			if (!tokenize_output_redirect((char *)input, shell, len))
				return (free_all(token, shell), NULL);
			input += len;
		}
		else if (*input == '|')
		{
			if (!tokenize_pipe((char *)input, shell))
				return (free_all(token, shell), NULL);
			input++;
		}
		else if (*input == '\'')
		{
			if (!tokenize_single_quotes(shell, (char *)input, len))
				return (free_all(token, shell), NULL);
		}
		else if (*input == '\"')
		{
			if (!tokenize_single_quotes(shell, (char *)input, len))
				return (free_all(token, shell), NULL);
		}
		else
		{
			if (!tokenize_word((char *)input, shell))
				return (free_all(token, shell), NULL);
		}
	}
	return (shell->head);
}
