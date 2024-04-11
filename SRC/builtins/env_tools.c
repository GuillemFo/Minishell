/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:32:24 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/11 11:20:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env_first(t_parser *parser, t_env **env, int i)
{
	t_env	*prev;
	char *tmp;
	
	tmp = get_til_equal(parser->cmd[i]);
	if ((*env)->name != NULL && ft_strcmp((*env)->name, tmp) == 0)
	{
		prev = (*env);
		(*env) = (*env)->next;
		free(prev->name);
		free(prev->content);
		free(prev);
		free(tmp);
	}
	free(tmp);
}

void	del_env(t_parser *parser, t_env **env, int i)
{
	t_env	*prev;
	t_env	*iter;
	char *tmp;

	del_env_first(parser, env, i);
	prev = NULL;
	iter = *env;
	while (iter != NULL)
	{
		tmp = get_til_equal(parser->cmd[i]);
		if (iter->name != NULL && ft_strcmp(iter->name, tmp) == 0)
		{
			if (prev == NULL)
				(*env) = iter->next;
			else
				prev->next = iter->next;
			free(iter->name);
			free(iter->content);
			free(iter);
			free(tmp);
			break;
		}
		free(tmp);
		prev = iter;
		iter = iter->next;
	}
}

void	edit_env(t_parser *parser, t_env **env, int i)
{
	t_env *iter;
	char *tmp;
	char *tmp2;

	iter = *env;
	while (iter)
	{
		tmp = get_til_equal(parser->cmd[i]);
		if (iter->name != NULL && ft_strcmp(iter->name, tmp) == 0)
		{
			free(iter->content);
			tmp2 = equal_til_end(parser->cmd[i]);
			if (env_has_equal(parser->cmd[i]) == 0)
			{
				iter->content = NULL;
				iter->is_hidden = true;
				free(tmp2);
				break;
			}
			iter->content = tmp2;
			iter->is_hidden = false;
			break;
		}
		free(tmp);
		//tmp = NULL;
		iter = iter->next;
	}
	free(tmp);
}

void	add_env(t_parser *parser, t_env **env, int i)
{
	t_env	*iter;

	if (!*env)
	{
		(*env) = malloc(sizeof(t_env));
		(*env)->name = get_til_equal(parser->cmd[i]);
		(*env)->is_hidden = env_no_value(parser->cmd[i]);
		(*env)->content = equal_til_end(parser->cmd[i]);
		(*env)->next = NULL;
		return;
	}
	iter = *env;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = malloc(sizeof(t_env));
	iter->next->name = get_til_equal(parser->cmd[i]);
	iter->next->is_hidden = env_no_value(parser->cmd[i]);
	iter->next->content = equal_til_end(parser->cmd[i]);
	iter->next->next = NULL;
}
