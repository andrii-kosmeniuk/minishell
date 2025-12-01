/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:38:51 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/01 15:19:54 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//note env - i bash gives you empty list
int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	//char	*line;
	t_data	data;
	t_shell	shell;

	init_env(&shell, &data, envp);
	list_key_value(&shell, envp, &data);
	update_shlvl_key(&shell, &data);
	print_env_list(shell.environment_p);
	/*while (1)
	{
		setup_signals();
		line = readline(CYAN"👹-minis(hell)>" RESET);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] != '\0')
			add_history(line);
		if (ft_strcmp(line, "clear") == 0)
			printf("\033[H\033[2J");
		free(line);
	}*/
	free_env_list(&shell, shell.environment_p);
	return (0);
}
