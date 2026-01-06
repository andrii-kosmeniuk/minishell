/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:26:28 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/28 01:49:06 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//what must i do?
//expansions rules:
//- if input is double quoted or not quoted at all -> perform expansions
//- if input is single quoted -> do not perform expansions at all
//
//with that in mind, we want to perform $? expansions and env variable expansion
//so given that a parameter is expandable (based on quote rule):
//if the character in the input is $ and the next one is ?, we expand it using
//the last exit status
//if the characters after it match any environmental variables key, we expand
//its value using getenv

static bool	is_valid(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (true);
	return (false);
}

char	*expand_string(char *input, t_env *env, int last_exit_status)
{
	char	*value;
	char	*string;
	char	*key;
	char	c;
	t_state	state;
	int		i;
	int		j;

	value = NULL;
	state = 0;
	i = 0;
	while (i < ft_strlen(input))
	{
		c = input[i];
		if ((c == '\'' && state != 2) || (c== '"' && state != 1))
		{
			if (c == '\'')
				state = 1;
			else
				state = 2;
			i++;
			continue ;
		}
		if (state != 1 && c == '$')
		{
			if (input[i + 1] == '?')
			{
				if (!ft_strcat(value, ft_itoa(last_exit_status)))
					return (NULL);
				input += 2;
				continue ;
			}
			if (input[i + 1] == '_' || (ft_isalpha(input[i + 1])))
			{
				j = i + 1;
				key = NULL;
				while (j < ft_strlen(input) && is_valid(input[j]))
					key[j++] = input[j++];
				while (env)
				{	
					if (ft_strcmp(key, env->key))
					{
						string = getenv(key);
						if (!string)
							return (NULL);
						ft_strcat(value, string);
					}
					else
						ft_strcat(value, "");
				env = env->next;
				}
				i = j;
				continue ;
			}
			else
			{
				ft_strcat(value, "$");
				i++;
				continue;
			}
		}
	}
	return (value);
}
