/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:29:06 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 18:46:25 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_export_entry(t_env *node)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(node->key, 1);
	if (node->value)
	{
		write(1, "=", 1);
		print_escaped_value(node->value);
	}
	write(1, "\n", 1);
}

static int	count_exported(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->exported)
			count++;
		env = env->next;
	}
	return (count);
}

static t_env	**collect_exported(t_env *env, int count)
{
	t_env	**arr;
	int		i;

	arr = ft_calloc(count + 1, sizeof(t_env *));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->exported)
			arr[i++] = env;
		env = env->next;
	}
	return (arr);
}

static void	sort_exported(t_env **arr, int count)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	export_print_sorted(t_shell *shell)
{
	int		count;
	t_env	**arr;
	int		i;

	count = count_exported(shell->environment_p);
	if (count == 0)
		return (0);
	arr = collect_exported(shell->environment_p, count);
	if (!arr)
		return (1);
	sort_exported(arr, count);
	i = 0;
	while (i < count)
	{
		print_export_entry(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
