/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/19 10:01:09 by gforns-s         ###   ########.fr       */
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

bool		env_exist(t_env *env, char *str)
{
	t_env *iter;
	iter = env;
	while (iter->next)
	{
		if (ft_strcmp(iter->name, str) == 0)
			return (true);
		iter = iter->next;
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


// t_env	*del_env(t_parser *token, t_env *env)	//THIS HAS A CHECKER IN ITSELF TO FILTER IF EXISTS OR NOT
// {
// 	t_env	*iter;
// 	t_env	*prev;
// 	t_env	*next;

// 	iter = env;
// 	if (env_exist(env, token) == true)
// 	{
// 		while (iter && iter->next)	//might not work due next->next
// 		{
// 			if (ft_strcmp(iter->next->name, token->cmd[1]) == 0)
// 			{
// 				prev = iter;
// 				next = iter->next->next;
// 				iter = iter->next;
// 				free(iter);
// 				prev->next = next;
// 			}
// 			iter = iter->next;
// 		}
// 	}
// 	return (env);
// }

// t_env	*edit_env(t_parser *parser, t_env *env) //THIS WILL ONLY MODIFY IF EXISTS> HAS TO CHECK IF EXISTS BEFORE
// {
// 
// }
// 


t_env	*add_env(t_parser *parser, t_env *env)	//WILL ONLY ADD, HAS TO CHECK IF EXISTS BEFORE
{
	t_env *iter;
	// int		len;
	iter = env;
	// len = ft_strlen(parser->cmd[1]);
	while (iter->next)
		iter = iter->next;		
	iter->next = malloc(sizeof(t_env));
	iter->next->name =ft_strdup(parser->cmd[0]);
	if (env_no_value(parser->cmd[1]) == true)
		iter->next->is_hidden = true;
	iter->next->content = ft_strdup(parser->cmd[1]);
	iter->next->next = malloc(sizeof(t_env));
	iter->next->next = NULL;
	return (env);
}

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
		start = x;
		x = x - 1;
		len = 0;
		while (var[++x] != '\0')
			len++;
		content = malloc((len + 1) * sizeof(char));
		x = -1;
		while (var[++start] != '\0')
			content[++x] = var[start];
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

