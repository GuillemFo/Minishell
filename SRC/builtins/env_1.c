/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/07 12:01:43 by codespace        ###   ########.fr       */
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

// bool		env_exist(t_env *env, t_parser *token)
// {
	// t_env *iter;
	// iter = env;
	// while (iter)	//might not work due next->next
	// {
		// if (ft_strcmp(iter->name, token->cmd[1]) == 0)	//maybe instead of returning true or 
																//false we can return the node where 
																//is located or NULL if not found
			// return (true);									//If i do this, i need to modify
		// iter = iter->next;									//the  way i return info  increate and delete env
	// }
	// return (false);
// }

char	*env_exist_2(t_env *env, char *name)
{
	t_env *iter;
	char *data;
	int	i;
	i = 0;
	iter = env;
	while (iter)	//might not work due next->next
	{
		if (ft_strcmp(iter->name, name) == 0)
		{
			data = malloc((ft_strlen(iter->content) + 1) * sizeof(char));
			while (iter->content[i] != '\0')
			{
				data[i] = iter->content[i];
				i++;
			}
			data[i] = '\0';
			return (data);
		}
		iter = iter->next;
	}
	data = malloc(sizeof(char));
	data[0] = '\0';
	return (data);
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


// t_env	*del_env(t_parser *token, t_env *env)
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


// t_env	*add_env(t_parser *token, t_env *env)
// {
// 	t_env *iter;
// 	iter = env;
// 	while (iter->next)
// 	{						//need to add  an exception for when the name already exists
// 		iter = iter->next;	//so we only modify the value. Or we can create a new function
// 	}						//for when the node exixts, use a new function that search on the list
// 							//and allow us to modify it
// 	iter->next = malloc(sizeof(t_env));
// 	iter->next->name = token->cmd[0];
// 	if (env_no_value(token->cmd[1]) == true)
// 		iter->next->is_hidden = true;
// 	iter->next->cmd = token->cmd[1];
// 	iter->next->next = malloc(sizeof(t_env));
// 	iter->next->next = NULL;
// 	return (env);
// }

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
