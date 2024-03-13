/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/13 17:03:29 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_poss_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

char	*get_home(t_env *env)
{
	t_env *iter;

	iter = env;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->name, "HOME") == 0)
			return (ft_strdup(iter->content));
		iter = iter->next;
	}
	return (ft_strdup("ERROR"));
}

// this works fine
bool	env_no_value(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	if (var[i] == '\0' || var[i + 1] == '\0')
		return (true);
	return (false);
}
// this works fine
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

// this works fine
int	print_hidden_lst(t_env *env)
{
	t_env	*iter;
	
	iter = env;
	while (iter != NULL)
	{	
		ft_printf("%s=\"%s\"\n", iter->name, iter->content);
		iter = iter->next;
	}
	return (0);
}

// this works fine
int	print_env_lst(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter != NULL)
	{
		if (iter->is_hidden == false)
			ft_printf("%s=\"%s\"\n", iter->name, iter->content);
		iter = iter->next;
	}
	return (0);
}

void	del_env(t_parser *parser, t_env **env, int i)
{
	t_env	*prev;
	t_env	*iter;

	if ((*env)->name != NULL && ft_strcmp((*env)->name, get_til_equal(parser->cmd[i])) == 0)
	{
		prev = (*env);
		(*env) = (*env)->next;
		free(prev->name);
		free(prev->content);
		free(prev);
	}
	prev = NULL;
	iter = *env;
	while (iter != NULL)
	{
		if (iter->name != NULL && ft_strcmp(iter->name,
				get_til_equal(parser->cmd[i])) == 0)
		{
			if (prev == NULL)
				(*env) = iter->next;
			else
				prev->next = iter->next;
			free(iter->name);
			free(iter->content);
			free(iter);
			break ;
		}
		prev = iter;
		iter = iter->next;
	}
}


t_env	*edit_env(t_parser *parser, t_env *env, int i)
{
	while (env)
	{
		if (env->name != NULL && ft_strcmp(env->name,
				get_til_equal(parser->cmd[i])) == 0)
		{
			free(env->content);
			env->content = ft_strdup(equal_til_end(parser->cmd[i]));
			break;
		}
		env = env->next;
	}
	return (env);
}

// Works fine
t_env	*add_env(t_parser *parser, t_env *env, int i)
{
	t_env	*iter;

	iter = env;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = malloc(sizeof(t_env));
	iter->next->name = ft_strdup(get_til_equal(parser->cmd[i]));
	iter->next->is_hidden = env_no_value(parser->cmd[i]);
	iter->next->content = ft_strdup(equal_til_end(parser->cmd[i]));
	iter->next->next = NULL;
	return (env);
}


char	*equal_til_end(char *var)
{
	int	x;

	x = 0;
	while (var[x] != '\0' && var[x] != '=')
		x++;
	if (var[x] == '=' && var[x + 1] != '\0')
		return (ft_strdup(var + x + 1));
	else
		return (ft_strdup("\"\""));
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

	env = malloc(sizeof(t_env));
	start = env;
	y = 0;
	while (envp[y] != NULL)
	{
		env->name = get_til_equal(envp[y]);
		env->is_hidden = env_no_value(envp[y]);
		env->content = equal_til_end(envp[y]);
		if (envp[y + 1] != NULL)
		{
			env->next = malloc(sizeof(t_env));
			env = env->next;
		}
		else
		{
			env->next = NULL;
		}
		y++;
	}
	return (start);
}
