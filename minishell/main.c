/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:38:51 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/15 22:16:15 by milija-h         ###   ########.fr       */
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
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	tokens = NULL;
	cmd = NULL;

	init_shell(&shell, &data, envp);
	list_key_value(&shell, envp, &data);
	update_shlvl_key(&shell, &data);

	while (1)
	{
		shell.redir_error = 0;
		setup_signals();
		line = readline(CYAN"👹-minis(hell)>" RESET);
		if (!line)
		{
			printf("exit\n");
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
		cmd = parse(&shell, tokens);
		t_token *tok = tokens;
		while (tok)
		{
			if (tok->redir && tok->redir->type == HERE_DOC)
			heredoc_append(tok->redir);
			tok = tok->next;
		}
		free_command(cmd);
		cmd = NULL;
		free_tokens(shell.head);
		shell.head = NULL;
		free(line);
	}
	free_command(cmd);
	cmd = NULL;
	if (shell.head)
	{
		free_tokens(shell.head);
		shell.head = NULL;
	}
	free_env_list(&shell, shell.environment_p);
	rl_clear_history();
	return (0);
}
