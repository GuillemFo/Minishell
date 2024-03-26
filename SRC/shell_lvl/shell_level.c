/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:56:09 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/26 07:20:22 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Works fine
void	add_env_shell(t_env **env)
{
	t_env	*iter;

	if (*env == NULL)
	{
		*env = malloc(sizeof(t_env));
		(*env)->name = ft_strdup("SHLVL");
		(*env)->content = ft_strdup("1");	//might cause leaks
		(*env)->is_hidden = false;
		(*env)->next = NULL;
		return;
	}
	iter = *env;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = malloc(sizeof(t_env));
	iter->next->name = ft_strdup("SHLVL");
	iter->next->content = ft_strdup("1");	//might cause leaks
	iter->next->is_hidden = false;
	iter->next->next = NULL;
}

void	shell_level(t_env **env)
{
	t_env *iter;
	int	holder;
	iter = *env;
	if (env_exist(*env, "SHLVL") == false)
		add_env_shell(env);
	else
	{
		while (iter)
		{
			if ((ft_strcmp("SHLVL", iter->name))== 0)	//Instead of this manycheckers maybe just count the amount of chars??
			{
				holder = ft_atoi(iter->content);
				if (holder <= 0 || holder > 1000)
				{
					if (holder <= 0)
						holder = -1;
					else
						holder = 0;
				}
				holder += 1;		//need a filter to check if value is gonna be more than 1000 to restore it to 1;
				if (holder > 1000)
				{
					errno_printer("warning", "shell level (%d) too high, holder", "resetting to 1");
					holder = 1;
				}
				iter->content = ft_itoa(holder);
				break;
			}
			iter = iter->next;
		}

	}
}

