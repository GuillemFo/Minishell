/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:22:21 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 12:10:19 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	parser_size(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser != NULL)
	{
		parser = parser->next;
		i++;
	}
	return (i);
}

char	**env_to_char(t_env *env)
{
	char	**new_env;
	char	*tmp;
	int		i;

	i = 0;
	new_env = my_malloc(sizeof(char *) * (env_size(env) + 1));
	while (env != NULL)
	{
		if (env->is_hidden == false)
		{
			tmp = ft_strjoini(env->name, "=");
			new_env[i] = ft_strjoini(tmp, env->content);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (env->is_hidden == false)
			i++;
		env = env->next;
	}
	return (i);
}

void	exec_error(char *message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}
