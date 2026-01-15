/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:38:51 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/12 14:33:27 by milija-h         ###   ########.fr       */
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
	t_token	*tokens = NULL;
	t_cmd	*cmd = NULL;
	t_state	state;

	(void)ac;
	(void)av;

	if (!init_shell(&shell, &state, &data, envp))
		return (printf("error init\n"), -1);
	list_key_value(&shell, envp, &data);
	update_shlvl_key(&shell, &data);

	while (1)
	{
		shell.redir_error = 0;
		setup_signals();
		line = readline(CYAN"👹-minis(hell)>" RESET);
		if (!line)
		{
			printf("exit1\n");
			break;
		}
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
			continue;
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
			continue;
		}

		//--------- testing command structure
		cmd = parse(&shell, tokens);
		if (!cmd)
			return (-1); //free necessary stuff upon fail
		print_cmd_structure(cmd);
		printf("\n\n");
		int i = 0;
		while (cmd->args[i])
		{
			printf("%s\n", cmd->args[i]);
			i++;
		}
		printf("\n\n");
	
	// -------- testing char ** content---------------

		char **argv = final_argvs(cmd->args[0], state, shell.environment_p, 0);
		if (!cmd->args[0])
		{
		   printf("Expansion failed\n");
			free_command(cmd);
			cmd = NULL;
			free(line);
			continue;
		}
		i = 0;
		while (argv[i])
		{
			printf("argv[%d] = [%s]\n", i, argv[i]);
			i++;
		}
		t_token *tok = tokens;
		while (tok)
		{
			if (tok->redir && tok->redir->type == HERE_DOC)
			heredoc_append(tok->redir);
			tok = tok->next;
		}
		free_command(cmd);
		cmd = NULL;
		//free(array);
		free_tokens(shell.head);
		shell.head = NULL;
		free(line);
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
