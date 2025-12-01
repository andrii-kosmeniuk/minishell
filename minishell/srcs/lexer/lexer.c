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
	t_token *t_node;
	const char	*start;
	char	*token_word;
	int		word_len;

	while (*input)
	{
		while (*input < 33)
			input++;
		if (!*input)
			break ;
		if (*input == '<')
		{
			if (*(input + 1) == '<')
			{
				t_node = create_token("<<", normal, HERE_DOC);
				if (!t_node)
					return (free_all(token, shell), NULL);
				add_token(&shell->head, t_node);
				input += 2;
			}
			else
			{
				t_node = create_token("<", normal, R_INPUT);
				if (!t_node)
					return (free_all(token, shell), NULL);
				add_token(&shell->head, t_node);
				input++;
			}
		}
		else if (*input == '>')
		{
			if (*(input + 1) == '>')
			{
				t_node = create_token(">>", normal, R_APPEND);
				if (!t_node)
					return (free_all(token, shell), NULL);
				add_token(&shell->head, t_node);
				input += 2;
			}
			else
			{
				t_node = create_token(">", normal, R_OUTPUT);
				if (!t_node)
					return (free_all(token, shell), NULL);
				add_token(&shell->head, t_node);
				input++;
			}
		}
		else if (*input == '|')
		{
			t_node = create_token("|", normal, PIPE);
			if (!t_node)
				return (free_all(token, shell), NULL);
			add_token(&shell->head, t_node);
			input++;
		}
		else
		{
			start = input;
			while (*input >= 33)
				input++;
			word_len = input - start;
			token_word = malloc(word_len + 1);
			if (!token_word)
				return (free_all(token, shell), NULL);
			token_word[0] = '\0';
			ft_strlcpy(token_word, input, input - start);
			t_node = create_token(token_word, normal, WORD);
			if (!t_node)
				return (free(token_word), free_all(token, shell), NULL);
			add_token(&shell->head, t_node);
			free(token_word);
			input += word_len;
		}
		input++;
	}
	return (shell->head);
}
