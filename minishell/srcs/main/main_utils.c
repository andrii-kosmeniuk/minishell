/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:16:23 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/05 20:16:41 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_line(char *line)
{
	int		i;
	size_t	len;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (0);
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'))
		line[--len] = '\0';
	return (1);
}

static int	process_heredocs(t_shell *shell, t_cmd *cmd, t_env *env)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == HERE_DOC || redir->type == R_APPEND)
		{
			setup_heredoc_signals();
			if (!heredoc_append(shell, redir, env))
			{
				restore_interactive_signals();
				return (0);
			}
			restore_interactive_signals();
		}
		redir = redir->next;
	}
	return (1);
}

int	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;
	int		exit_status;

	exit_status = 0;
	if (ft_strcmp(line, "clear") == 0)
		return (printf("\033[H\033[2J"), 1);
	tokens = build_token_list(line, shell);
	if (!tokens || shell->redir_error || !syntax_check(shell))
		return (printf("syntax error1\n"), cleanup_tokens(shell), 0);
	cmd = parse(shell, tokens);
	if (!cmd)
		return (printf("Error parsing\n"), cleanup_tokens(shell), 0);
	if (!expand_all(shell, cmd, shell->environment_p))
		return (printf("Error expanding\n"), free_command(cmd),
			cleanup_tokens(shell), 0);
	if (!process_heredocs(shell, cmd, shell->environment_p))
		return (free_command(cmd), cleanup_tokens(shell), 0);
	if (builtin_check(cmd) && (cmd->redirections || cmd->next))
		exit_status = execute_pipeline(cmd, shell);
	else if (is_builtin(cmd, shell))
		exit_status = shell->exit_status;
	else
		exit_status = execute_pipeline(cmd, shell);
	free_command(cmd);
	cleanup_tokens(shell);
	return (exit_status);
}
int	init_minishell(t_shell *shell, t_state *state, t_data *data, char **envp)
{
	if (!init_shell(shell, state, data))
		return (printf("Error initializing shell\n"), 0);
	list_key_value(shell, envp, data);
	update_shlvl_key(shell, data);
	setup_interactive_signals();
	return (1);
}

int	shell_loop(t_shell *shell)
{
	char	*line;
	int		exit_status;

	while (1)
	{
		shell->redir_error = 0;
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
			continue ;
		}
		if (!is_valid_line(line))
		{
			free(line);
			continue ;
		}
		exit_status = add_process_free(line, shell);
	}
	return (exit_status);
}
