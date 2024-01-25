/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/25 13:00:01 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool		env_exist(t_env *env, t_parser *token)
{
	if (ft_strcmp(env->name, token->content[1]) == 0)
		return (true);

	return (false);
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

char	*get_til_equal(char *var)
{
	int	x;
	int len;
	char *name;
	x = 0;
	while (var[x] != '=')
		x++;
	len = x +1;
	x = 0;
	name = malloc(len * sizeof(char));
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
	int	y;
	
	y = 0;
	while (envp[y] != NULL)
	{
		env = malloc(sizeof(t_env));
		env->name = get_til_equal(envp[y]);
		env->content = equal_til_end(envp[y]);
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
		y++;
	}
	env = malloc(sizeof(t_env));
	return (env);
}

