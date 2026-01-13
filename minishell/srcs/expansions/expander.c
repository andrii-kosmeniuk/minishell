/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:17:33 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/13 11:17:49 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		expand_command(t_cmd *cmd, t_env *env, int exit_code);
int		expand_arguments(t_cmd *cmd, t_env *env, int exit_code);
char	*expand_string(char *input, t_state state, t_env *env, int exit_code);
int		expand_redirections(t_cmd *cmd, t_env *env, int exit_code);
char	**expand_word(char *word, t_state state, t_env *env, int exit_code);
char	*expand_target(char *target, t_state state, t_env *env, int exit_code);
char	**word_split(char *expanded);

bool		is_single_word(char *expanded);
char	*get_value(t_env *env, char *variable_name);
bool	is_valid(char c);



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
