/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:44:02 by milija-h          #+#    #+#             */
/*   Updated: 2026/02/16 22:01:47 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*static bool	select_expand_mode(t_token *cur, t_token *next)
{
	bool	expand;

	if (cur->should_expand == true && next->should_expand = true)
		return (expand = true);
	else if (cur->should_expand == false && next->should_expand == false)
		return (expand = false);
	else if (cur->expand)
}*/

static bool	should_merge(t_token *cur, t_token *next)
{
	if (!next)
		return (false);
	if (next->has_space_before == true)
		return (false);
	if ((cur->type == WORD || cur->type == S_QUOTE || cur->type == D_QUOTE) &&
		(next->type == WORD || next->type == S_QUOTE || next->type == D_QUOTE))
		return (printf("evil\n"), true);
	return (true);
}

/*static char	*expand_token(t_env *env, t_token *cur, t_token *next)
{
	char	*content;
	char	*expanded_cur;

	{
		expanded_cur = cur->content;
		expanded_cur++;
		content = get_value(env, expanded_cur);
		if (!content)
			content = ft_strdup("");
		free(cur->content);
		cur->content = NULL;
		cur->content = ft_strdup(content);
		if (!cur->content)
			cur->content = ft_strdup("");
		free(content);
		content = NULL;
	}
	return (cur->content);
}*/

bool	merge_tokens(t_token *tokens, t_env *env)
{
	t_token	*cur;
	t_token	*next;
	char	*merged;
	char	*cur_key;

	cur = tokens;
	print_tokens(tokens);
	if (cur->next)
	{
		while (cur)
		{
			next = cur->next;
			if (should_merge(cur, next))
			{
				int i = 0;
				while (cur->content[i])
				{
					if (cur->content[i] == '$' && cur->should_expand)
						cur_key = ft_strdup(cur->content + 1);
					printf("cur_key is: %s\n", cur_key);
					cur->content = get_value(env, cur_key);
					if (!cur->content)
						return (printf("issues\n"), false);
					i++;
					/*free(cur->content);
					cur->content = NULL;*/
				}
				i = 0;
				//while (next->content[i])
				//if (next->)
				//worksa
				merged = ft_strjoin(cur->content, next->content);
				if (!merged)
					return (false);
				free(cur->content);
				cur->content = NULL;
				cur->content = ft_strdup(merged);
				if (!cur->content)
					return (free(merged), false);
				cur->type = WORD;
				free(merged);
				merged = NULL;
				/*if (cur->should_expand == false && next->should_expand == true)
					cur->should_expand = false;*/
				printf("cur->should_expand is: %d\n", cur->should_expand);
				cur->next = next->next;
				free(next->content);
				next->content = NULL;
				free(next);
				next = NULL;
				//until here
			}
			else
				cur = cur->next;
		}
	}
	print_tokens(tokens);
	return (true);
}
