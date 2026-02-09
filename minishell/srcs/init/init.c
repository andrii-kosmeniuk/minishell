/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:23:53 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/01 22:31:50 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	init_shell(t_shell *shell, t_state *state, t_data *data)
{
	data->shlvl = 1;
	*state = normal;
	shell->redir_error = 0;
	data->heredoc_number = 0;
	shell->environment_p = NULL;
	shell->head = NULL;
	return (true);
}
