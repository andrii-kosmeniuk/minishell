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

char	*expand_string(t_shell *shell, char *input, t_env *env)
{
	t_expand	p;

	p.output = NULL;
	p.len = 0;
	p.exit_code = 0;
	p.env = env;
	while (*input)
	{
		if (*input == '$')
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

static char **split_expanded(char *expanded)
{
    char **argv;

    if (!expanded)
        return (NULL);

    argv = word_split(expanded);
    free(expanded);
    return (argv);
}

char	**no_expansions(char *input)
{
	char	*duplicate;

	duplicate = ft_strdup(input);
	if (!duplicate)
		return (NULL);
	return (split_expanded(duplicate));
}

char	**expand_args(t_shell *shell, char *input, t_env *env)
{
	char	*expanded;

	if (ft_strchr(input, '$'))
		expanded = expand_string(shell, input, env);
	else
		expanded = ft_strdup(input);
	if (!expanded)
		return (NULL);
	return (split_expanded(expanded));
}
