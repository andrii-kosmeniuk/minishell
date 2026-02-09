/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:24:57 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/09 13:25:10 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	execve_error(char *cmd_name)
{
	if (errno == ENOENT)
	{
		perror(cmd_name);
		exit(127);
	}
	else if (errno == EACCESS)
	{
		perror(cmd_name);
		exir(126);
	}
	else
	{
		perror(cmd_name);
		exit(126);
	}
}

void	fork_error(void)
{
	perror("fork");
}
