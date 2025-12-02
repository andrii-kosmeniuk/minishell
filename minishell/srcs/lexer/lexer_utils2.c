/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:09:10 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/01 22:09:11 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	add_token_list(t_token **token, t_state state, t_type type, char *value)
{
	t_token	*t_node;

	t_node = create_node(value, state, type);
	if (!t_node)
		return (false);
	add_token(token->head, t_node);
	return (true);
}

// <
// <<
bool	tokenize_input_redirect(const char *input, t_shell *shell, int len)
{
	if (input[1] == '<')
	{
		if (input[2] == '<')
		{
			len = 2;
			if (!add_token_list(&shell->head, normal, HERE_DOC, "<<"))
				return (false);
		}
		else
		{
			len = 1;
			if (!add_token_list(&shell->head, normal, R_INPUT, "<"))
				return (false);
		}
	}
	return (true);
}

// >
// >>
bool	tokenize_output_redirect(const char *input, t_shell *shell, int len)
{
	if (input[1] == '>')
	{
		if (input[2] == '>')
		{
			len = 2;
			if (!add_token_list(&shell->head, normal, R_APPEND, ">>"))
				return (false);
		}
		else
		{
			len = 1;
			if (!add_token_list(&shell->head, normal, R_OUTPUT, ">"))
				return (false);
		}
	}
	return (true);
}

// |
bool	tokenize_pipe(const char *input, t_shell *shell)
{
	if (input[1])
	{
		if (!add_token_list(&shell->head, normal, PIPE, "|"))
			return (false);
	}
	return (true);
}

//not operators
bool	tokenize_word(const char *input, t_shell *shell)
{
	char	*start_of_word;
	char	*token_word;
	int		word_len;

	start_of_word = input;
	while (*input >= 33)
		input++;
	world_len = input - start;
	token_word = malloc(world_len + 1);
	if (!token_word)
		return (false);
	token_word[0] = '\0';
	ft_strlcpy(token_word, input, input - start);
	if (!add_token_list(&shell->head, normal, WORD, token_word))
		return (free(token_word), false);
	free(token_word);
	return (true);
}
