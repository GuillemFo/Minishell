/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/04 06:39:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env_exist(t_env *env, char *str)
{
	t_env	*iter;

	iter = env;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->name, str) == 0)
			return (true);
		iter = iter->next;
	}
	return (false);
}


char	*equal_til_end(char *var)
{
	int	x;

	x = 0;
	while (var[x] != '\0' && var[x] != '=')//this will stop before =
		x++;
	if (var[x] == '=' && var[x + 1] != '\0')
	{
		return (ft_strdup(var + x + 1));
	}
	// 08.19 igual con este filtro lo soluciono
	else if (var[x] == '=' && var[x + 1] == '\0')
		return (ft_strdup(""));
	return (NULL);	//si devuelvo null me petan los siguientes?? De momento no funciona. 07.16 am 
}


char	*get_til_equal(char *var)
{
	int		x;
	int		len;
	char	*name;

	x = 0;
	while (var[x] != '=' && var[x] != '\0')
		x++;
	len = x + 1;
	name = malloc(len * sizeof(char));
	if (!name)
		return (NULL);
	x = 0;
	while (var[x] != '=' && var[x] != '\0')
	{
		name[x] = var[x];
		x++;
	}
	name[x] = '\0';
	return (name);
}


t_env	*load_env(char **envp)
{
	t_env	*env;
	t_env	*start;
	int		y;

	if(envp == NULL || envp[0] == NULL)
		return (NULL);
	env = malloc(sizeof(t_env));
	start = env;
	y = -1;
	while (envp[++y] != NULL)
	{
		env->name = get_til_equal(envp[y]);
		env->is_hidden = !env_has_equal(envp[y]);
		env->content = equal_til_end(envp[y]);
		if (envp[y + 1] != NULL)
		{
			env->next = malloc(sizeof(t_env));
			env = env->next;
		}
		else
			env->next = NULL;
	}
	return (start);
}