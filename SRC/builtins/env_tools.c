/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:32:24 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/25 14:38:23 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


void	edit_env(t_parser *parser, t_env **env, int i)
{
	t_env *iter;

	iter = *env;
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
}


void	add_env(t_parser *parser, t_env **env, int i)
{
	t_env	*iter;

	if (!*env)
	{
		(*env) = malloc(sizeof(t_env));
		(*env)->name = ft_strdup(get_til_equal(parser->cmd[i]));
		(*env)->is_hidden = env_no_value(parser->cmd[i]);
		(*env)->content = ft_strdup(equal_til_end(parser->cmd[i]));
		(*env)->next = NULL;
		return;
	}
	iter = *env;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = malloc(sizeof(t_env));
	iter->next->name = ft_strdup(get_til_equal(parser->cmd[i]));
	iter->next->is_hidden = env_no_value(parser->cmd[i]);
	iter->next->content = ft_strdup(equal_til_end(parser->cmd[i]));
	iter->next->next = NULL;
}
