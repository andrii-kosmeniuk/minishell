/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:22:25 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/25 14:22:46 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	cd_update_env(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (old_pwd && old_pwd[0])
		env_set(&shell->environment_p, "OLDPWD", old_pwd, true);
	if (new_pwd)
	{
		env_set(&shell->environment_p, "PWD", new_pwd, true);
		free(new_pwd);
	}
}

static int	cd_chdir(char *path, t_shell *shell, char *old_pwd)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	cd_update_env(shell, old_pwd);
	return (0);
}

static int	cd_home(t_shell *shell, char *old_pwd)
{
	char	*home;

	home = get_env_value(shell, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	return (cd_chdir(home, shell, old_pwd));
}

static int	cd_oldpwd(t_shell *shell, char *old_pwd)
{
	char	*oldpwd;

	oldpwd = get_env_value(shell, "OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	printf("%s\n", oldpwd);
	return (cd_chdir(oldpwd, shell, old_pwd));
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	old_pwd[1024];
	char	*path;

	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	if (!cmd->args[1])
		return (cd_home(shell, old_pwd));
	if (ft_strcmp(cmd->args[1], "-") == 0)
		return (cd_oldpwd(shell, old_pwd));
	path = cmd->args[1];
	return (cd_chdir(path, shell, old_pwd));
}
