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
	(void)ac;
	(void)av;

	char	*line;
	t_env	*env;
	t_env	*head;
	t_data	data;
	t_shell	shell;

	init_env(&shell, envp);
	env = create_list_key_value(&shell, &head, envp);
	while (1)
	{
		setup_signals();
		line = readline(CYAN"👹-minis(hell)>" RESET);
		if (!line)
		{
			printf("shell has been killed\n");
			break ;
		}
		if (line[0] != '\0')
			add_history(line);
		if (ft_strcmp(line, "clear") == 0)
			printf("\033[H\033[2J");
		free(line);
	}
	return (0);
}
