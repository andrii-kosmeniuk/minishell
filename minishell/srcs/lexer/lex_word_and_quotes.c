/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_word_and_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:09:10 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/03 22:40:20 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	tokenize_word(const char *input, t_shell *shell, int *len)
{
	const char	*start_of_word;
	char		*token_word;
	int			word_len;

	start_of_word = input;
	while (*input >= 33)
		input++;
	word_len = input - start_of_word;
	token_word = ft_calloc(word_len + 1, sizeof(char));
	if (!token_word)
		return (false);
	ft_strncpy(token_word, start_of_word, word_len);
	if (!build_list(shell, normal, WORD, token_word))
		return (free(token_word), false);
	*len = ft_strlen(token_word);
	free(token_word);
	return (true);
}

static void	get_state(t_shell *shell, char quote)
{
	if (quote == '\'')
		shell->state = single_q;
	else if (quote == '\"')
		shell->state = double_q;
}

static char	*extract_quoted_string(t_shell *shell, char *input, int *len)
{
	char	*start_of_string;
	char	*quoted_string;
	char	quote;

	quote = *input;
	input++;
	get_state(shell, quote);
	start_of_string = input;
	while (*input && *input != quote)
		input++;
	if (*input == '\0' && shell->state != normal)
	{
		shell->state = normal;
		*len = input - start_of_string + 1;
		return (NULL);
	}
	shell->state = normal;
	quoted_string = ft_calloc(input - start_of_string + 1, sizeof(char));
	if (!quoted_string)
		return (NULL);
	ft_strncpy(quoted_string, start_of_string, input - start_of_string);
	*len = input - start_of_string + 2;
	return (quoted_string);
}

bool	tokenize_single_quotes(t_shell *shell, char *input, int *len)
{
	char	*quoted_input;
	t_token	*t_node;

	quoted_input = extract_quoted_string(shell, input, len);
	if (!quoted_input)
		return (false);
	t_node = build_list(shell, single_q, S_QUOTE, quoted_input);
	if (!t_node)
		return (free(quoted_input), false);
	free(quoted_input);
	return (true);
}

bool	tokenize_double_quotes(t_shell *shell, char *input, int *len)
{
	char	*quoted_input;
	t_token	*t_node;

	quoted_input = extract_quoted_string(shell, input, len);
	if (!quoted_input)
		return (false);
	t_node = build_list(shell, double_q, D_QUOTE, quoted_input);
	if (!t_node)
		return (free(quoted_input), false);
	free(quoted_input);
	return (true);
}
