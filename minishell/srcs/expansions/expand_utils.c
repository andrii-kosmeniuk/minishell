/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:25:51 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/13 14:27:38 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	append_var(char **buf, size_t *len, t_env *env, char *var_name)
{
	char	*value;

	value = get_value(env, var_name);
	if (!value)
		return (true);
	printf("value appended is: %s\n", value);
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

//find a way to use last $? here
bool	append_exit_code(t_shell *shell, char **buf, size_t *len)
{
	char	*tmp;

	tmp = ft_itoa(shell->exit_status);
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

bool	handle_expansions(char **input, t_expand *expand, t_shell *shell)
{
	char	*key;

	key = NULL;
	if (*(*input + 1) == '?')
	{
		if (!append_exit_code(shell, &expand->output, &expand->len))
			return (false);
		(*input) += 2;
	}
	else if (is_valid(*(*input + 1)))
	{
		key = read_variable_name(*input, *input + 1);
		if (!key)
			return (false);
		printf("key is: %s\n", key);
		if (!append_var(&expand->output, &expand->len, expand->env, key))
			return (free(key), false);
		(*input) += 1 + ft_strlen(key);
		free(key);
	}
	return (true);
}
