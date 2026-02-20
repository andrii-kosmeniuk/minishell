/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_word_and_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:27:20 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/04 13:51:37 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*extract_quoted_string(t_shell *shell, char *input, int *len,
									t_state *quote_state)
{
	char	*start_of_string;
	char	*quoted_string;
	char	quote;

	quote = *input;
	input++;
	get_state(shell, quote);
	*quote_state = shell->state;
	start_of_string = input;
	while (*input && *input != quote)
		input++;
	if (*input == '\0' && shell->state != normal)
	{
		shell->state = normal;
		*len = input - start_of_string + 1;
		return (NULL);
	}
	quoted_string = ft_calloc(input - start_of_string + 1, sizeof(char));
	if (!quoted_string)
		return (NULL);
	ft_strncpy(quoted_string, start_of_string, input - start_of_string);
	*len = input - start_of_string + 2;
	return (quoted_string);
}

int	tokenize_word(char *input, t_shell *shell, int *len)
{
	char	*start_of_word;
	char	*token_word;
	int		word_len;
	bool	should_expand;

	start_of_word = input;
	while (*input && !my_isspace(*input) && *input != '\'' && *input != '\"'
		&& *input != '<' && *input != '>' && *input != '|')
		input++;
	word_len = input - start_of_word;
	token_word = ft_calloc(word_len + 1, sizeof(char));
	if (!token_word)
		return (1);
	ft_strncpy(token_word, start_of_word, word_len);
	should_expand = (shell->state != single_q);
	if (!build_list(shell, WORD, token_word, should_expand))
		return (free(token_word), 1);
	*len = ft_strlen(token_word);
	free(token_word);
	return (0);
}

void	get_state(t_shell *shell, char quote)
{
	if (shell->state == normal && quote == '\'')
		shell->state = single_q;
	else if (shell->state == normal && quote == '\"')
		shell->state = double_q;
	else if (shell->state == single_q && quote == '\'')
		shell->state = normal;
	else if (shell->state == double_q && quote == '\"')
		shell->state = normal;
}

bool	tokenize_single_quotes(t_shell *shell, char *input, int *len)
{
	char	*quoted_input;
	t_token	*t_node;
	t_state	quote_state;

	quoted_input = extract_quoted_string(shell, input, len, &quote_state);
	if (!quoted_input)
		return (false);
	t_node = build_list(shell, S_QUOTE, quoted_input, false);
	if (!t_node)
		return (free(quoted_input), false);
	shell->state = normal;
	free(quoted_input);
	return (true);
}

bool	tokenize_double_quotes(t_shell *shell, char *input, int *len)
{
	char	*quoted_input;
	t_token	*t_node;
	t_state	quote_state;

	quoted_input = extract_quoted_string(shell, input, len, &quote_state);
	if (!quoted_input)
		return (false);
	t_node = build_list(shell, D_QUOTE, quoted_input, true);
	if (!t_node)
		return (free(quoted_input), false);
	shell->state = normal;
	free(quoted_input);
	return (true);
}
