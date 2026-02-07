/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:20:04 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/15 21:18:15 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*const char *type_to_string(t_type type)
{
    if (type == WORD) return "WORD";
    if (type == PIPE) return "PIPE";
    if (type == R_INPUT) return "R_INPUT (<)";
    if (type == R_OUTPUT) return "R_OUTPUT (>)";
    if (type == R_APPEND) return "R_APPEND (>>)";
    if (type == HERE_DOC) return "HERE_DOC (<<)";
    return "UNKNOWN";
}

void print_tokens(t_token *tokens)
{
    printf("\n========= TOKENS =========\n");

    int i = 0;

    while (tokens)
    {
        printf("[%d]\n", i);
        printf(" type    : %s\n", type_to_string(tokens->type));
        printf(" content : %s\n", tokens->content ? tokens->content : "NULL");
        printf(" next    : %p\n", (void *)tokens->next);
        printf("------------------------\n");

        tokens = tokens->next;
        i++;
    }

    printf("======= END TOKENS =======\n\n");
}


void print_redirs(t_redir *redir)
{
    if (!redir)
    {
        printf("    (none)\n");
        return;
    }

    int i = 0;

    while (redir)
    {
        printf("    [%d]\n", i);
        printf("     type   : %s\n", type_to_string(redir->type));
        printf("     target : %s\n", redir->target);
        printf("     next   : %p\n", (void *)redir->next);
        redir = redir->next;
        i++;
    }
}


void print_argv(char **argv)
{
    if (!argv)
    {
        printf("    argv: NULL\n");
        return;
    }

    int i = 0;

    while (argv[i])
    {
        printf("    argv[%d] = [%s]\n", i, argv[i]);
        i++;
    }
}


void print_commands(t_cmd *cmd)
{
    printf("\n=========== COMMAND LIST ===========\n");

    int cmd_i = 0;

    while (cmd)
    {
        printf("\n===== COMMAND %d =====\n", cmd_i);

        printf("  argv pointer : %p\n", (void *)cmd->args);
        printf("  redir pointer: %p\n", (void *)cmd->redirections);
        printf("  next pointer : %p\n\n", (void *)cmd->next);

        printf("  ARGUMENTS:\n");
        print_argv(cmd->args);

        printf("\n  REDIRECTIONS:\n");
        print_redirs(cmd->redirections);

        printf("\n============================\n");

        cmd = cmd->next;
        cmd_i++;
    }

    printf("\n========= END COMMANDS =========\n\n");
}


void debug_print_all_argv(t_cmd *cmd)
{
    int i;

    while (cmd)
    {
        i = 0;
        printf("COMMAND:\n");

        while (cmd->args && cmd->args[i])
        {
            printf("argv[%d] = [%s]\n", i, cmd->args[i]);
            i++;
        }

        printf("\n");
        cmd = cmd->next;
    }
}*/
