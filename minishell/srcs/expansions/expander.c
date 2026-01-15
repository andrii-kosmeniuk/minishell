/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:17:33 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/15 10:56:24 by milija-h         ###   ########.fr       */
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
	return (tmp);
}

char	*expand_string(char *input, t_state state, t_env *env, int exit)
{
	char	*output;
	size_t	len;
	char	*key;

	output = NULL;
	len = 0;
	while (*input)
	{
		if (*input == '$' && state != single_q)
		{
		    if (*(input + 1) == '?')
		    {
		        if (!append_exit_code(&output, &len, exit))
		            return (free(output), NULL);
		        input += 2;
		    }
		    else if (is_valid(*(input + 1)))
		    {
		        key = read_variable_name(input, input + 1);
				if (!key)
					return (free(key), free(output), NULL);
		        if (!append_var(&output, &len, env, key))
		            return (free(key), free(output), NULL);
		        input += 1 + ft_strlen(key);
		        free(key);
		    }
		else
		    append_char(&output, &len, *input++);
		}
	}
	return (output);
}

char	**final_argvs(char *input, t_state state, t_env *env, int exit)
{
	char	**argv;
	char	*expanded;

	argv = NULL;
	expanded = NULL;
	expanded = expand_string(input, state, env, exit);
	if (!expanded)
		return (NULL);
	argv = word_split(expanded);
	if (!argv)
		return (free(expanded), NULL);
	return (argv);
}
