/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/06 12:27:46 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	env_exist(t_env *env, char *str) // this works fine
{
	t_env *iter;
	int len;
	iter = env;
	while (iter->next)
	{
		len = ft_strlen(str);
		if (ft_strncmp(iter->name, str, len) == 0)
			return (true);
		iter = iter->next;
	}
	return (false);
}

int	print_hidden_lst(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter != NULL)
	{
		ft_printf("%s=%s\n", iter->name, iter->content);
		iter = iter->next;
	}
	return (0);
}

int	print_env_lst(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter != NULL)
	{
		if (iter->is_hidden == false)
			ft_printf("%s=%s\n", iter->name, iter->content);
		iter = iter->next;
	}
	return (0);
}

// NOT WORKING
t_env	*del_env(t_parser *parser, t_env *env)
{
	t_env	*prev;
	t_env	*iter;
	int		len;

	prev = NULL;
	iter = env;
	len = ft_strlen(get_til_equal(parser->cmd[1]));
	while (iter != NULL)
	{
		if (iter->name != NULL && strncmp(iter->name, parser->cmd[1], len) == 0)
		{
			if (prev == NULL)
				env = iter->next;
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
	return (env);
}

// THIS WILL ONLY MODIFY IF EXISTS> HAS TO CHECK IF EXISTS BEFORE
t_env	*edit_env(t_parser *parser, t_env *env)
{
	int	len;

	len = strlen(parser->cmd[1]);
	while (env != NULL)
	{
		if (env->name != NULL && strncmp(env->name,
				get_til_equal(parser->cmd[1]), len) == 0)
		{
			free(env->content);
			env->content = strdup(equal_til_end(parser->cmd[1]));
			break ;
		}
		env = env->next;
	}
	return (env);
}


t_env	*add_env(t_parser *parser, t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter)
		iter = iter->next;
	iter->next = malloc(sizeof(t_env));
	iter->next->name = ft_strdup(get_til_equal(parser->cmd[1]));
	iter->next->is_hidden = env_no_value(parser->cmd[1]);
	iter->next->content = ft_strdup(equal_til_end(parser->cmd[1]));
	iter->next->next = malloc(sizeof(t_env));
	iter->next->next = NULL;
	return (env);
}

char	*equal_til_end(char *var)
{
	int		x;
	int		start;
	int		len;
	char	*content;

	x = 0;
	while (var[x] != '\0' && var[x] != '=')
		x++;
	if (var[x] == '=' && var[x + 1] != '\0')
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
		content[++x] = '\0';
		return (content);
	}
	else
		content = ft_strdup("\"\"");
	return (content);
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




