/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:51:43 by milija-h          #+#    #+#             */
/*   Updated: 2026/01/11 18:51:45 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**final_argv(char *input, t_env *env)
{
	char	*expanded;
	char	**argv;

	expanded = NULL;
	argv = NULL;
	expanded = final_expand(input, env);
	if (!expanded)
		return (NULL);
	argv = word_splitting(expanded);
	if (!argv)
		return (free(expanded), NULL);
	free(expanded);
	return (argv);
}
