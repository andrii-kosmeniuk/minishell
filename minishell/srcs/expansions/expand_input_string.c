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

static bool	append_var(char **buf, size_t *len, t_env *env, char *var_name)
{
	char	*value;

	value = get_value(env, var_name);
	if (!value)
		return (true);
	if (!append_string(buf, len, value))
	{
		free(value);
		value = NULL;
		return (false);
	}
	free(value);
	value = NULL;
	return (true);
}

static bool	append_exit_code(char **buf, size_t *len, int exit_code)
{
	char	*tmp;

	tmp = ft_itoa(exit_code);
	if (!tmp)
		return (false);
	if (!append_string(buf, len, tmp))
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	return (true);
}

static bool	handle_expansions(char **input, t_expand *expand)
{
	char	*key;

	key = NULL;
	if (*(*input + 1) == '?')
	{
		if (!append_exit_code(&expand->output, &expand->len, expand->exit_code))
			return (false);
		(*input) += 2;
	}
	else if (is_valid(*(*input + 1)))
	{
		key = read_variable_name(*input, *input + 1);
		if (!key)
			return (false);
		if (!append_var(&expand->output, &expand->len, expand->env, key))
			return (free(key), false);
		(*input) += 1 + ft_strlen(key);
		free(key);
	}
	return (true);
}

char	*expand_string(char *input, t_env *env, int exit)
{
	t_expand	p;

	p.output = NULL;
	p.len = 0;
	p.exit_code = exit;
	p.env = env;
	while (*input)
	{
		if (*input == '$')
		{
			if (!handle_expansions(&input, &p))
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

char	**final_args(char *input, t_env *env, bool should_expand, int exit)
{
	char	**argv;
	char	*expanded;

	if (!should_expand)
		expanded = ft_strdup(input);
	else if (ft_strchr(input, '$'))
		expanded = expand_string(input, env, exit);
	else
		expanded = ft_strdup(input);
	if (!expanded)
		return (perror("failed final args"), NULL);
	argv = word_split(expanded);
	if (!argv)
		return (free(expanded), NULL);
	free(expanded);
	return (argv);
}
