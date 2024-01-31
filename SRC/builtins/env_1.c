/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/31 18:07:20 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	env_has_value(char *var)
{
	int i;
	i = 0;
	while (var[i] != '=')
		i++;
	if (var[i +1] == '\0')
		return (false);
	return (true);
}

bool		env_exist(t_env *env, t_parser *token)
{
	if (ft_strcmp(env->name, token->content[1]) == 0)
		return (true);

	return (false);
}

int	print_env_lst(t_env *env)
{
	while (env->name)
	{
		if (env->is_hidden == false)
			ft_printf("%s=%s\n", env->name, env->content);	//this will always print the = after an enviroment is set. 
		env = env->next;									//might need a function to check if it has = on it when creating a new one.
	}														//maybe add a new flag on the t_env struct to??
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
	while (var[x] != '=' || var[x] != '\0')
		x++;
	len = x +1;
	name = malloc(len * sizeof(char));
	x = 0;
	while (var[x +1] != '\0' || var[x +1] != '=')
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
	int	y;
	
	y = 0;
	while (envp[y] != NULL)
	{
		env = malloc(sizeof(t_env));
		env->name = get_til_equal(envp[y]);
		env->is_hidden = env_has_value(envp[y]);
		env->content = equal_til_end(envp[y]);
		env = env->next;
		y++;
	}
	//env = malloc(sizeof(t_env));
	return (env);
}

