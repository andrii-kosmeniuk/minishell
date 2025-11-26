/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:38:51 by milija-h          #+#    #+#             */
/*   Updated: 2025/11/22 21:05:57 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_env	env;
	char	*prompt;

	(void)ac;
	(void)av;
	init_env(&shell, envp);
	env = create_list_key_value(&shell, &shell->environment_p ,envp);
	if (!env)
		return (1);
	prompt = prompt("👹minis(hell)$1");
	if (!prompt)
		return (1);
	return (0);
}
