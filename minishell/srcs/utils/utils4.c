/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:35:44 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 14:21:49 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_necessary(char **array, size_t i)
{
	while (i > 0)
		free(array[--i]);
	free(array);
	array = NULL;
}

static size_t	list_size(t_env *env)
{
	t_env	*cur;
	size_t	count;

	cur = env;
	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

static char	*join_env(char *key, char *value)
{
	size_t	len;
	char	*str;
	size_t	key_len;
	size_t	value_len;

	if (!value)
		return (ft_strdup(key));
	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	len = ft_strlen(key) + ft_strlen(value) + 2;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, key, key_len);
	str[key_len] = '=';
	ft_memcpy(str + key_len + 1, value, value_len);
	str[key_len + value_len + 1] = '\0';
	return (str);
}

//use inside of child processes before execve
char	**list_to_envp(t_shell *shell)
{
	t_env	*cur;
	size_t	len;
	size_t	i;
	char	**env_array;

	cur = shell->environment_p;
	len = list_size(cur);
	env_array = ft_calloc(len + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	while (cur)
	{
		env_array[i] = join_env(cur->key, cur->value);
		if (!env_array[i])
			return (free_necessary(env_array, i), NULL);
		i++;
		cur = cur->next;
	}
	return (env_array);
}
