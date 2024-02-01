/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/01 10:31:38 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env_no_value(char *var)
{
	int i;
	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	if (var[i] == '\0' || var[i + 1] == '\0')
		return (true);
	return (false);
}

bool		env_exist(t_env *env, t_parser *token)
{
	t_env *top;
	top = env;
	while (top)
	{
		if (ft_strcmp(top->name, token->content[1]) == 0)
			return (true);
		top = top->next;
	}
	return (false);
}

int	print_env_lst(t_env *env)
{
	t_env *iter;
	iter = env;
	while (iter->next)
	{
		if (iter->is_hidden == false)
			ft_printf("%s=%s\n", iter->name, iter->content);
		iter = iter->next;
	}
	return (0);
}

/*
t_env	*del_env()
{
	

}

t_env	*add_env()
{

}
*/

char	*equal_til_end(char	*var)
{
	int		x;
	int		start;
	int 	len;
	char	*content;
	
	x = 0;
	while (var[x] != '=')
		x++;
	if (var[x + 1] != '\0')
	{
		start = x + 1;
		x = x + 1;
		len = 0;
		while (var[x] != '\0')
		{
			len++;
			x++;
		}
		content = malloc((len + 1) * sizeof(char));
		x = 0;
		while (var[start] != '\0')
		{
			content[x] = var[start];
			x++;
			start++;
		}
		content[x] = '\0';
		return (content);
	}
	else
		content = NULL;
	return (content);
}


char	*get_til_equal(char *var)
{
	int	x;
	int len;
	char *name;
	x = 0;
	while (var[x] != '=')
		x++;
	len = x +1;
	name = malloc(len * sizeof(char));
	x = 0;
	while (var[x] != '=')
	{
		name[x] = var[x];
		x++;
	}
	name[x] = '\0';
	return (name);
}

t_env	*load_env(char **envp)
{
	t_env		*env;
	t_env		*start;
	int	y;
	
	y = 0;
	env = malloc(sizeof(t_env));
	start = env;
	while (envp[y] != NULL)
	{
		env->name = get_til_equal(envp[y]);
		env->is_hidden = env_no_value(envp[y]);
		env->content = equal_til_end(envp[y]);
		env->next = malloc(sizeof(t_env));
		env = env->next;
		y++;
	}
	env->next = NULL;
	return (start);
}

