/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:22:04 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/04 12:55:35 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_string(t_shell *shell, bool *expand, char *input, t_env *env)
{
	t_expand	p;

	p.output = NULL;
	p.len = 0;
	p.exit_code = 0;
	p.env = env;
	while (*input)
	{
		if (*input == '$' && *expand)
		{
			if (!handle_expansions(&input, &p, shell))
				return (free(p.output), NULL);
			continue ;
		}
		if (!append_char(&p.output, &p.len, *input))
			return (free(p.output), NULL);
		input++;
	}
	if (!p.output)
		return (ft_strdup(""));
	return (p.output);
}
