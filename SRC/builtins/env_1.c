/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/05 10:25:09 by gforns-s         ###   ########.fr       */
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
	int		len;
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


t_env	*del_env(t_parser *parser, t_env *env)	// NOT WORKING
{
	t_env	*iter;
	t_env	*prev;
	t_env	*next;
	int		len;
	
	iter = env;
	while (iter->next)	//might not work due next->next
	{
		len = ft_strlen(get_til_equal(parser->cmd[1]));
		if (ft_strncmp(iter->next->name, parser->cmd[1], len) == 0)
		{
			prev = iter;
			if (iter->next->next)
				next = iter->next->next;
			else
				next = NULL;
			iter = iter->next;
			free(iter);
			prev->next = next;
		}
		iter = iter->next;
	}
	return (env);
}


//THIS WILL ONLY MODIFY IF EXISTS> HAS TO CHECK IF EXISTS BEFORE
t_env	*edit_env(t_parser *parser, t_env *env)
{
	t_env *iter;
	iter = env;
	char	*name;
	name = get_til_equal(parser->cmd[1]);
	while (iter->next && (strcmp(name, iter->name) != 0))
		iter = iter->next;
	iter->content = equal_til_end(parser->cmd[1]);
	return(env);
}


	//WILL ONLY ADD, HAS TO CHECK IF EXISTS BEFORE
t_env	*add_env(t_parser *parser, t_env *env)
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

// NOT WORKIG PROPERLY
char	*equal_til_end(char	*var)
{
	int		x;
	int		start;
	int 	len;
	char	*content;
	
	x = 0;
	while (var[x] != '\0' && var[x] != '=' )
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
		content[++x] = '\0';
		return (content);
	}
	else
		content = ft_strdup("empty");
	return (content);
}


char	*get_til_equal(char *var)
{
	int	x;
	int len;
	char *name;
	x = 0;
	while (var[x] != '=' && var[x] != '\0')
		x++;
	len = x +1;
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

