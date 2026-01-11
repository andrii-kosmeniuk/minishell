/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:26:28 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/11 18:11:02 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//what must i do?
//expansions rules:
//- if input is double quoted or not quoted at all -> perform expansions, remove
//quotes, no word splitting
//- if input is unquoted word spliiting is performed
//- if input is single quoted -> do not perform expansions at all, remove quotes
//
//so:
//echo $USER                   $SHLVL, becomes:
//milija-h 2
//
//echo "$USER                   $SHLVL", becomes:
//milija-h                      2
//
//echo '$USER                   $'
//
//with that in mind, we want to perform $? expansions and env variable expansion
//so given that a parameter is expandable (based on quote rule):
//if the character in the input is $ and the next one is ?, we expand it using
//the last exit status
//if the characters after it match any environmental variables key, we expand
//its value using getenv

static char	*handle_single_quotes(char *input, char *expanded_string)
{
	input++;
	while (*input && *input != '\'')
	{
		append_char(expanded_string, *input);
		input++;
	}
	if (*input != '\'')
		return (printf("unclosed single quote\n"), NULL);
	return (input + 1);
}

static char	*double_unquoted(t_env *env, char *input, char *expanded_str)
{
	t_state	state;
	char	*var_name;
	char	*exit_str;
	char	*value;
	int		exit_status;

	exit_status = 0;
	state = normal;
	while (*input)
	{
		if (state == normal)
		{
			if (*input == '\'')
				break ;
			if (*input == '"')
			{
				state = double_q;
				input++;
				continue ;
			}
		}
		else if (state == double_q)
		{
			if (*input == '"')
			{
				state = normal;
				input++;
				continue ;
			}
		}
		if (*input == '$' && *(input + 1) == '?')
		{
			exit_str = ft_itoa(exit_status);
			if (!exit_str)
				return (NULL);
			ft_strcat(expanded_str, exit_str);
			free(exit_str);
			input += 2;
			continue ;
		}
		if (*input == '$' && is_valid(*(input + 1)))
		{
			var_name = read_variable_name(input, input + 1);
			if (!var_name)
				return (NULL);
			value = get_value(env, var_name);
			if (!value)
				value = "";
			ft_strcat(expanded_str, value);
			input += 1 + ft_strlen(var_name);
			free(var_name);
			continue ;
		}
		append_char(expanded_str, *input);
		input++;
    }
	return (input);
}

char	*expand(char *input, t_env *env)
{
	char	*expanded;
	char	*new_pos;

	if (!input)
		return (NULL);
	expanded = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!expanded)
		return (NULL);
	while (*input)
	{
		if (*input == '\'')
		{
			new_pos = handle_single_quotes(input, expanded);
			if (!new_pos)
				return (free(expanded), NULL);
			input = new_pos;
		}
		else
		{
			new_pos = double_unquoted(env, input, expanded);
			if (!new_pos)
				return (free(expanded), NULL);
			input = new_pos;
		}
	}
	return (expanded);
}
