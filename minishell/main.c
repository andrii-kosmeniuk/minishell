/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:38:51 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/26 18:37:07 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_shell	shell;
	t_state	state;

	(void)ac;
	(void)av;
	if (!init_minishell(&shell, &state, &data, envp))
		return (-1);
	shell.exit_status = shell_loop(&shell);
	cleanup_shell(&shell);
	return (0);
}
