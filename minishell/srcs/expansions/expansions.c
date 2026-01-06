/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:26:28 by milija-h          #+#    #+#             */
/*   Updated: 2025/12/28 01:49:06 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//what must i do?
//expansions rules:
//- if input is double quoted or not quoted at all -> perform expansions, remove
//quotes, no word splitting
//- if input is unquoted word spliiting is performed
//- if input is single quoted -> do not perform expansions at all, remove quotes
//
//so:
//echo $USER                   $SHLVL, becomes:
//milija-h 2
//
//echo "$USER                   $SHLVL", becomes:
//milija-h                      2
//
//echo '$USER                   $'
//
//with that in mind, we want to perform $? expansions and env variable expansion
//so given that a parameter is expandable (based on quote rule):
//if the character in the input is $ and the next one is ?, we expand it using
//the last exit status
//if the characters after it match any environmental variables key, we expand
//its value using getenv

static bool	is_valid(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (true);
	return (false);
}

