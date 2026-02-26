/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 22:59:33 by akosmeni          #+#    #+#             */
/*   Updated: 2026/02/26 23:00:15 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_loop_readline(t_shell *shell, char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (-1);
	}
	if (g_signal == 130)
	{
		shell->exit_status = 130;
		g_signal = 0;
		free(line);
		return (0);
	}
	return (1);
}
