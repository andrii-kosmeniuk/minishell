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
	if (ft_isalpha(c) || c == '_')
		return (true);
	return (false);
}

static	char *get_value(t_env *env, char *variable_name)
{
	t_env	*cur;
	char	*value;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, variable_name))
		{
			value = getenv(variable_name); //OR MAYBE value = ft_strdup(cur->value)?
			if (!value)
			{
				value = ft_strdup("");
				if (!value)
					return (NULL);
			}
		}
		cur = cur->next;
	}
	return (value);
}

char	*expand_string(char *input, t_env *env, int exit_code)
{
	t_state	state;
	int		number_of_quotes;
	char	quote;
	char	*result;
	char	*value;

	(void)exit_code;
	result = NULL;
	while (*input)
	{
		state = 0;
		number_of_quotes = 0;
		if (*input == '\'')
		{
			number_of_quotes = 1;
			quote = *input;
			while (*input)
			{
				if (*input == '\'')
					number_of_quotes++;
				input++;
			}
			if (*input == '\0' && number_of_quotes % 2 != 0)
				return (printf("unclosed single quotes\n"), NULL);
			state = 1;
			//logic here is -> no expansion, just append full input to result
			ft_strlcat(result, input, *input - quote); //allocate with malloc?
			input++;
		}
		else if (*input == '\"')
		{
			quote = *input;
			while (*input)
			{
				if (*input == '\"')
					number_of_quotes++;
				input++;
			}
			if (*input == '\0' && number_of_quotes % 2 != 0)
				return (printf("unclosed double quotes\n"), NULL);
			state = 2;
			input = &quote;
			while (*input)
			{
				if (*input == '$')
				{
					if (!is_valid(*(input + 1))) //if first variable name does not start with letter or _, error
						return (NULL);
					value = get_value(env, input);
					if (!value)
						return (NULL);
					ft_strcat(result, value);
					input += ft_strlen(value);
				}
				input++;
			}
		}
		input++;
	}
	return (result);;
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

    char *tests[] = {
        "$milija",
        "No expansion here",
        "Hello $user!",
        "Mixed $milija-$user",
        NULL
    };

    for (int i = 0; tests[i]; i++)
    {
        char *result = expand_string(tests[i], env, 0);
        /*if (!result)
            printf("Error expanding: %s\n", tests[i]);*/
        //else
        //{
            printf("Input: \"%s\" --> Expanded: \"%s\"\n", tests[i], result);
            free(result);  // Assuming expand_string allocates memory
        //}
    }

    free_env(env);
    return 0;
}
