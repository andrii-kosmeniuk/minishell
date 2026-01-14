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

static char	*handle_single_quotes(char *input, char *expanded, size_t *pos)
{
	input++;
	while (*input && *input != '\'')
	{
		expanded[(*pos)++] = *input;
		input++;
	}
	if (*input != '\'')
		return (printf("unclosed single quote\n"), NULL);
	return (input + 1);
}

static char	*expand(t_env *env, char *input, char *expanded, size_t *position)
{
	t_state	state;
	char	*var_name;
	char	*exit_str;
	char	*value;

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
			exit_str = ft_itoa(0);//Use actual exit status
			if (!exit_str)
				return (NULL);
			ft_memcpy(expanded + *position, exit_str, ft_strlen(exit_str));
			*position += ft_strlen(exit_str);
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
			ft_memcpy(expanded + *position, value, ft_strlen(value));
			*position += ft_strlen(value);
			input += 1 + ft_strlen(var_name);
			free(var_name);
			continue ;
		}
		expanded[(*position)++] = *input;
		input++;
	}
	return (input);
}

char	*final_expand(char *input, t_env *env)
{
	char	*expanded;
	char	*new_pos;
	size_t	estimated_size;
	size_t	position = 0;

	if (!input)
		return (NULL);
	estimated_size = calculate_expanded_size(input, env);
	expanded = ft_calloc(estimated_size, sizeof(char));
	if (!expanded)
		return (NULL);
	while (*input)
	{
		if (*input == '\'')
		{
			new_pos = handle_single_quotes(input, expanded, &position);
			if (!new_pos)
				return (free(expanded), NULL);
			input = new_pos;
		}
		else
		{
			new_pos = expand(env, input, expanded, &position);
			if (!new_pos)
				return (free(expanded), NULL);
			input = new_pos;
		}
	}
	return (expanded);
}








char	*expand_string(char *input, t_state state, t_env *env, int exit_code)
{
	char	*expanded;
	char	*exit_string;
	char	*quoted_section;
	char	*value;
	char	*key;

	expanded = ft_calloc(1, sizeof(char))
	if (!expanded)
		return (NULL);
	value = NULL;
	while (*input)
	{
		if (state == normal && *input == '\'')
		{
			//dont perform expansions indicate unclosed quote if so
			state = single_q;
			quoted_section = input + 1; // pointing to first word after quote
			while (*input && *input != '\'')
				input++;
			if (*input != '\'')
				return (printf("unclosed quoted\n"), free(expanded), NULL);
			expanded = ft_realloc(expanded, ft_strlen(expanded),
						 input - quoted_section + 1);
			if (!expanded)
				return (free(expanded), NULL);
			ft_memcpy(expanded + ft_strlen(expanded), quoted_section,
			input - quoted_section);
			state = normal;
			input++;
			continue ;
		}
		if (*input == '$' && *(input + 1) == '?')
		{
			exit_string = ft_itoa(exit_code);
			if (!exit_string)
				return (free(expanded), NULL);
			expanded = ft_realloc(expanded, ft_strlen(expanded),
				  ft_strlen(exit_string));
			if (!expanded)
				return (free(exit_string, free(expanded), NULL));
			ft_memcpy(expanded + ft_strlen(expanded), exit_string,
				ft_strlen(exit_string));
			free(exit_string);
			exit_string = NULL;
			input +2;
			continue ;
		}
		if (state == normal && *input == '"')
		{
			quoted_section = input + 1;
			while (*input && *input != '"')
				input++;
			if (*input != '\'')
				return (printf("unclosed quotes\n"), free(expanded), NULL)
			state = double_q;
			input = quoted_section;
			if (*input == '$' && is_valid(*(input + 1));
			{
				key = read_variable_name(input, quoted_section)
				if (!key)
					return (free(expanded), NULL);
				value = get_value(env, key)
				if (!value)
					return (free(key), free(expanded), NULL);
				expanded = ft_realloc(expanded, ft_strlen(expanded),
						  ft_strlen(value));
				if (!expanded)
					return (free(key), free(expanded), NULL);
				ft_memcpy(expanded + ft_strlen(expanded), value,
					ft_strlen(value));
				free(key);
				key = NULL;
				state = normal;
				input += ft_strlen(value) + 1;
				continue ;
			}
		}
		expanded = ft_realloc(expanded, ft_strlen(expanded),
					 ft_strlen(expanded) + 1)
		ft_memcpy(expanded + ft_strlen(expanded), &input[i], 1);
		input++;
	}
}
