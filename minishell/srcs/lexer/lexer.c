/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:09:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/01 22:40:58 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*build_token_list(t_token *token, const char *input, t_shell *shell)
{
	while (*input)
	{
		while (*input < 33)
			input++;
		if (*input == '<')
		{
			if (!tokenize_input_redirect(input, shell, len))
				return (free_all(token, shell), NULL);
			input += len;
		}
		else if (*input == '>')
		{
			if (!tokenize_output_redirect(input, shell))
				return (free_all(token, shell), NULL);
			input += len;
		}
		else if (*input == '|')
		{
			if (!tokenize_pipe(input, shell))
				return (free_all(token, shell), NULL);
			input++;
		}
		else
		{
			if (!tokenize_word(input, shell))
				return (free_all(token, shell), NULL);
		}
	}
	return (shell->head);
}
