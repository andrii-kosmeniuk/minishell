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

static int	handle_single_quotes(char *input, int i, char *expanded_string)
{
	input[i] == '\''
	i++;
	while (input[i] && input[i] != '\'')
	{
		*output[i] = input[i];
		i++;
	}
	if (input[i] != '\'')
		return (printf("unclosed single quote\n"), 0);
	i++;
	return (i);
}

static int	double_unquoted(char *input, int i, char *expanded_string)
{
	t_state	state;
	char	*var_name;
	char	*exit_str;
	int		i;
	int		exit_status;
	
	state = normal;
	while (input[i])
	{
		if (state == normal)
		{
			if (input[i] == '\'')
				break ;
			if (input[i] == '"')
			{
				state = double_q;
				i++;
				continue ;
			}
		}
		else if (state == double_q)
		{
			if (input[i] == '"')
			{
				state = normal;
				i++;
				continue ;
			}
		}
		if (input[i] == '$' && input[i + 1] == '$')
		{
			//exit_status = get_exit_status(exit_status);
			exit_str = ft_itoa(exit_status);
			if (!exit_str)
				return (0);
			ft_strcat(output, exit_str);
			i += 2;
		}
		if (input[i] == '$' && is_valid(input[i + 1]))
		{
			var_name = input;
			value = get_value(var_name);
			if (!value)
			{
				value = ft_strdup("");
				if (!value)
					return (0);
			}
			ft_strcat(expanded_string, value);
			i += 1 + ft_strlen(var_name);
			continue ;
		}
		ft_strcat(output, input[i]);
		i++;
	}
	return (i);
}

static char	*expand(char *input)
{
	char	*expanded;
	int		i;

	expanded = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!expanded)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			i = handle_single_quotes(input, i, expanded);
		else
			i = double_unquoted(input, i, expanded);
		i++:
	}
	input[i] = '\0';
	return (expanded);
}

t_env *create_env(void)
{
    t_env *head = malloc(sizeof(t_env));
    t_env *second = malloc(sizeof(t_env));

    head->key = strdup("milija");
    head->value = strdup("hello");
    head->next = second;

    second->key = strdup("user");
    second->value = strdup("world");
    second->next = NULL;

    return head;
}

// Free the environment list
void free_env(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env;
        env = env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

int main(void)
{
    t_env *env = create_env();

    /*char *tests[] = {
        "$milija",
        "No expansion here",
        "Hello $user!",
        "Mixed $milija-$user",
        NULL
    };*/

	char *input = "$milija";

    for (int i = 0; input[i]; i++)
    {
        char *result = expand_string(input, env, 0);
        /*if (!result)
            printf("Error expanding: %s\n", tests[i]);*/
        //else
        //{
            printf("Input: \"%s\" --> Expanded: \"%s\"\n", input, result);
            free(result);  // Assuming expand_string allocates memory
        //}
    }

    free_env(env);
    return 0;
}
