/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:38:51 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/05 15:55:03 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;
	t_shell	shell;
	t_token	*tokens = NULL;
	t_cmd	*cmd = NULL;
	t_state	state;
	int		only_spaces;
	int		i;
	size_t	len;
	
	(void)ac;
	(void)av;
	if (!init_shell(&shell, &state, &data, envp))
		return (printf("Error initializing shell\n"), -1);
	list_key_value(&shell, envp, &data);
	update_shlvl_key(&shell, &data);
	setup_interactive_signals();
	while (1)
	{
		shell.redir_error = 0;
		g_signal = 0;
		line = readline(CYAN"👹-minis(hell)>" RESET);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal == 1)
		{
			g_signal = 0;
			free(line);
			continue;
		}
		only_spaces = 1;
		i = 0;
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\t')
			{
				only_spaces = 0;
				break ;
			}
			i++;
		}
		if (only_spaces)
		{
			free(line);
			continue ;
		}
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'))
			line[--len] = '\0';
		if (*line)
			add_history(line);
		if (shell.head)
		{
			free_tokens(shell.head);
			shell.head = NULL;
		}
		if (ft_strcmp(line, "clear") == 0)
		{
			printf("\033[H\033[2J");
			free(line);
			continue ;
		}
		tokens = build_token_list(line, &shell);
		if (!tokens || shell.redir_error)
		{
			printf("syntax error\n");
			if (shell.head)
			{
				free_tokens(shell.head);
				shell.head = NULL;
			}
			free(line);
			continue ;
		}
		cmd = parse(&shell, tokens);
		if (!cmd)
		{
			printf("Error parsing\n");
			free_tokens(shell.head);
			shell.head = NULL;
			free(line);
			continue ;
		}
		char **argv = expand_final_args(tokens, shell.environment_p, 0);
		if (!argv)
		{
			printf("Expansion failed\n");
			free_command(cmd);
			cmd = NULL;
			free(line);
			continue ;
		}
		t_redir	*redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == HERE_DOC || redir->type == R_APPEND)
			{
				setup_heredoc_signals();
				if (!heredoc_append(redir, shell.environment_p, 0))
				{
					restore_interactive_signals();
					break ;
				}
				restore_interactive_signals();
			}
			redir = redir->next;
		}
		i = 0;
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				printf("%s\n", cmd->args[i]);
				i++;
			}
		}
		i = 0;
		while (argv[i])
		{
			printf("argv[%d] = [%s]\n", i, argv[i]);
			i++;
		}
		free_command(cmd);
		cmd = NULL;
		if (shell.head)
		{
			free_tokens(shell.head);
			shell.head = NULL;
		}
		free(line);
		free_array(argv);
	}
	if (shell.head)
	{
		free_tokens(shell.head);
		shell.head = NULL;
	}
	free_env_list(&shell, shell.environment_p);
	rl_clear_history();
	return (0);
}
