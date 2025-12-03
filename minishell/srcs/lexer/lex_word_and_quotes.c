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

bool	tokenize_word(const char *input, t_shell *shell)
{
	const char	*start_of_word;
	char		*token_word;
	int			word_len;

	start_of_word = input;
	while (*input >= 33)
		input++;
	word_len = input - start_of_word;
	token_word = malloc(word_len + 1);
	if (!token_word)
		return (false);
	token_word[0] = '\0';
	ft_strlcpy(token_word, input, input - start_of_word);
	if (!build_list(shell, normal, WORD, token_word))
		return (free(token_word), false);
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

static char	*extract_quoted_string(t_shell *shell, char *input)
{
	char	*start_of_string;
	char	*quoted_string;
	char	quote;

	while (*input && *input != '\'' && *input != '\"')
		input++;
	quote = *input;
	input++;
	get_state(shell, quote);
	start_of_string = input;
	while (*input && *input != quote)
		input++;
	if (*input == '\0' && shell->state != normal)
	{
		fprintf(stderr, "unclosed quote\n");
		return (NULL);
	}
	shell->state = normal;
	quoted_string = ft_calloc(input - start_of_string + 1, sizeof(char));
	if (!quoted_string)
		return (NULL);
	ft_strncpy(quoted_string, start_of_string, input - start_of_string);
	return (quoted_string);
}

bool	tokenize_single_quotes(t_shell *shell, char *input, size_t len)
{
	char	*quoted_input;
	t_token	*t_node;

	quoted_input = extract_quoted_string(shell, input);
	if (!quoted_input)
		return (false);
	len = ft_strlen(quoted_input);
	t_node = build_list(shell, single_q, S_QUOTE, quoted_input);
	if (!t_node)
		return (free(quoted_input), NULL);
	free(quoted_input);
	return (true);
}

bool	tokenize_double_quotes(t_shell *shell, char *input, size_t len)
{
	char	*quoted_input;
	t_token	*t_node;

	quoted_input = extract_quoted_string(shell, input);
	if (!quoted_input)
		return (false);
	len = ft_strlen(quoted_input);
	t_node = build_list(shell, double_q, D_QUOTE, quoted_input);
	if (!t_node)
		return (false);
	free(quoted_input);
	return (true);
}
