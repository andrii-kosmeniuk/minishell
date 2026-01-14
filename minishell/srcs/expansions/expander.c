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

static bool	append_var(char **buf, size_t *len, t_env *env, char *var_name)
{
	char	*value;

	value = get_value(env, var_name);
	if (!value)
		return (true);
	if (!append_str(buf, len, value))
	{
		free(value);
		value = NULL;
		return (false);
	}
	free(value);
	value = NULL;
	return (true);
}

static char	*append_exit_code(char **buf, size_t *len, int exit_code)
{
	char	*tmp;

	tmp = ft_itoa(exit_code);
	if (!tmp)
		return (false);
	if (!append_string(buf, len, tmp))
	{
		free(tmp);
		tmp = NULL;
		return (false);
	}
	free(tmp);
	tmp = NULL;
	return (exit_str);
}

char	*expand_string(char *input, t_state state, t_env *env, int exit)
{
	char	*output;
	size_t	len;
	char	*value;

	output = NULL;
	len = 0;
	while (*input)
	{
		state = determine_state(state, input);
		if (state != single_q && *input == '$')
		{
			if (*(input + 1) == '?')
			{
				if (!append_exit_code())
			}
		}
	}
	return (output);
}
