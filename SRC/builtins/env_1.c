/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/17 04:41:37 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	reminder cant go over 1000	|| NOT MODIFYIG WHEN LAST NODE (not set before)
t_env	*shell_level(t_env *env)
{
	t_env *iter;
	int	holder;
	iter = env;
	if (env_exist(env, "SHLVL") == false){
		//printf("FALSE\n");
		env = add_env_shell(env);}
	else
	{
		while (iter)
		{
			if ((ft_strcmp("SHLVL", iter->name))== 0)
			{
				holder = ft_atoi(iter->content);
				if (holder <= 0 || holder > 1000)
				{
					if (holder <= 0)
						holder = -1;
					else
						holder = 0;
				}
				iter->content = ft_itoa(holder + 1);		//need a filter to check if value is gonna be more than 1000 to restore it to 1;
			//printf("--%s--\n", iter->content);
				break;
			}
			iter = iter->next;
		}
	}
	return (env);
}


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
	if (var[i] == '\0')
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
		ft_printf("declare -x %s=\"%s\"\n", iter->name, iter->content);
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
			ft_printf("%s=%s\n", iter->name, iter->content);
		iter = iter->next;
	}
	return (1);
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

//am i returning the env losing before nodes when iterating??
// Should i start an iter so i can iter = env and iterate the copy and not lose the top?
// Why i havent seen this before?? Changed envto iter so wont lose first node.
t_env	*edit_env(t_parser *parser, t_env *env, int i)
{
	t_env *iter;

	iter = env;
	while (iter)
	{
		if (iter->name != NULL && ft_strcmp(iter->name,
				get_til_equal(parser->cmd[i])) == 0)
		{
			free(iter->content);
			iter->content = ft_strdup(equal_til_end(parser->cmd[i]));
			break;
		}
		iter = iter->next;
	}
	return (env);
}

// Works fine
t_env	*add_env_shell(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = malloc(sizeof(t_env));
	iter->next->name = ft_strdup("SHLVL");
	iter->next->content = ft_strdup("1");
	iter->next->next = NULL;
	return (env);
}

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
	if (var[x] == '=' && var[x + 1] != '\0')	//need to add a filter so wont coppy ';'
		return (ft_strdup(var + x + 1));
	else
		return (ft_strdup(""));
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
