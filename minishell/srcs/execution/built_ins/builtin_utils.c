/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:40:26 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/12 13:41:43 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		new_line = 0;
		++i;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line == 1)
		printf("\n");
	return (0);
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	old_pwd[1024];
	char	s[100];

	printf("%s\n", getcwd(s, 100));
	if (cmd->args[1] == NULL)
	{
		path = get_env_value(shell, "HOME");
		if (chdir(path) != 0)
			perror("cd home:");
		printf("%s\n", getcwd(s, 100));
		return (0);
	}
	else if (ft_strcmp(cmd->args[1], "-"))
	{
		getcwd(old_pwd, 200);
		path = get_env_value(shell, "OLDPWD");
		if (chdir(path) != 0)
			perror("cd home:");
		printf("%s\n", getcwd(s, 100));
		return (0);
	}
	path = cmd->args[1];
	if (chdir(path) != 0)
		perror("minishell: cd: ");
	return (1);
}

int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
		return (0);
	}
	perror("getcwd: ");
	return (1);
}

int	ft_export(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

int	ft_unset(t_cmd *cmd, t_env *env)
{
	t_cmd	*cur;
	t_env	*var;
	t_env	*prev;
	int		i;

	prev = NULL;
	var = env;
	cur = cmd;
	i = 1;
	while (cur->args[i])
	{
		while (var)
		{
			printf("args is: %s\n", cur->args[i]);
			printf("var_key is: %s\n", var->key);
			if (ft_strcmp(cur->args[i], var->key) == 0)
			{
				printf("b\n");
				if (prev == NULL)
					env = var->next;
				else
					prev->next = var->next;
				free(var->value);
				free(var->key);
				free(var);
				break ;
			}
			prev = var;
			var = var->next;
		}
		i++;
	}
	return (0);
}
