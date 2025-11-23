/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:20:22 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/20 20:20:24 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//this build our own envp
//env_array is allocated for total len of envp + NULL terminator at the end
//this stores enough space for the full length of the array from envp[1][i] to
//envp[n][last char]
//
//to build each env variable which by default are strings, we must also allocate
//memory for each of them (remember, env variables follow a KEY=value design)
//
//this will be later passed to execve()

char	**copy_of_envp(t_shell *shell, char **envp)
{
	int	i;

	if (!envp)
		return (NULL); //copy minimum env??
	i = 0;
	while (envp[i])
	{
		shell->env_array[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!shell->env_array[i])
			return (allocation_failed(envp, i), NULL);
		ft_strcpy(shell->env_array[i], envp[i]);

		i++;
	}
	shell->env_array[len_size(envp)] = NULL;
	return (shell->env_array);
}

//this build a linked list full of the key and values of the env variables
//each node has one key and one value (KEY=value), so we loop until = is found,
//all to the left is KEY rest is value
//
//we can also check for duplicates here, if a duplicate variable is found, we 
//keep the last (as per what BASH does)

int	duplicated_key(t_shell *)
{
	;
}

void	create_list_key_value(t_shell *shell, t_env **head, char **envp)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*node;

	if (envp[0] == NULL)
		build_minimum_env(shell);
	while (*envp)
	{
		equal_sign = ft_strchr((*envp, '='));
		if (!equal_sign)
		{
			key = ft_strndup(*envp);
			if (!key)
				return ;
			value = NULL;
		}
		else
		{	
			key = ft_strndup(*envp, equal_sign - *envp);
			if (!key)
				return ;
			if (ft_strncmp(key, envp[i], ft_strlen(key)) == 0)
			{
				ft_strcpy(, key);
				free(key);
			}
			value = ft_strdup(equal_sign + 1);
			if (!value)
				return (free(key));
		}
		node = create_node(key, value);
		if (!node)
			return (free(value), free(key));
		add_to_list(head, node);
		envp++;
	}
	shell->environment_p = *head;
}
