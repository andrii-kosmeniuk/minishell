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

bool		add_token_to_list(t_token **token, t_shell *shell, char *value);
const char	*tokenize_input_redirect(const char *input, t_shell *shell);
const char	*tokenize_output_redirect(const char *input, t_shell *shell);
const char	*tokenize_pipe(const char *input, t_shell *shell);
const char	*tokenize_word(const char *input, t_shell *shell);
