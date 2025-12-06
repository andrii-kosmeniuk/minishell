/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:38:51 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/03 22:32:10 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//note env - i bash gives you empty list

//extern volatile		sig_atomic_t	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;
	t_shell	shell;
	t_token	*tokens;

	(void)ac;
	(void)av;
	tokens = NULL;
	init_shell(&shell, &data, envp);
	list_key_value(&shell, envp, &data);
	update_shlvl_key(&shell, &data);
	while (1)
	{
		setup_signals();
		line = NULL;
		line = readline(CYAN"👹-minis(hell)>" RESET);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
		{
			if (line[0] != '\0')
				add_history(line);
			if (ft_strcmp(line, "clear") == 0)
			{
				printf("\033[H\033[2J");
				free(line);
				continue;
			}
			shell.head = NULL;
			tokens = build_token_list(line, &shell);
			if (!tokens)
				return (free_env_list(&shell,
						  shell.environment_p), free(line), 1);
			print_tokens(tokens);
			print_num_of_tokens(tokens);
			free_tokens(tokens);
		}
		free(line);
	}
	free_env_list(&shell, shell.environment_p);
	rl_clear_history(); 
	return (0);
}
