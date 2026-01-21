/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:22:04 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/16 21:25:21 by milija-h         ###   ########.fr       */
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

char	*expand_string(char *input, t_env *env, int exit)
{
	char	*output;
	size_t	len;
	char	*key;

	output = NULL;
	key = NULL;
	len = 0;
	while (*input)
	{
		if (*input == '$')
		{
			if (*(input + 1) == '?')
			{
				if (!append_exit_code(&output, &len, exit))
					return (free(output), NULL);
				input += 2;
				continue ;
			}
			else if (is_valid(*(input + 1)))
			{
				key = read_variable_name(input, input + 1);
				if (!key)
					return (free(output), NULL);
				if (!append_var(&output, &len, env, key))
					return (free(output), NULL);
				input += 1 + ft_strlen(key);
				free(key);
				continue ;
			}
		}
		if (!append_char(&output, &len, *input))
			return (free(output), NULL);
		input++;
	}
	return (output);
}

char	**final_args(char *input, bool should_expand, t_env *env, int exit)
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
		return (NULL);
	argv = word_split(expanded);
	if (!argv)
		return (free(expanded), NULL);
	free(expanded);
	return (argv);
}
