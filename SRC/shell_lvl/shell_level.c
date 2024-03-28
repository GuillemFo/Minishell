/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:56:09 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/28 15:51:57 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	add_env_shell(t_env **env)
{
	t_env	*iter;

	if (*env == NULL)
	{
		*env = malloc(sizeof(t_env));
		(*env)->name = ft_strdup("SHLVL");
		(*env)->content = ft_strdup("1");
		(*env)->is_hidden = false;
		(*env)->next = NULL;
		return;
	}
	iter = *env;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = malloc(sizeof(t_env));
	iter->next->name = ft_strdup("SHLVL");
	iter->next->content = ft_strdup("1");
	iter->next->is_hidden = false;
	iter->next->next = NULL;
}

void	shell_level(t_env **env)
{
	t_env	*iter;
	long long	holder;
	iter = *env;
	if (env_exist(*env, "SHLVL") == false)
		add_env_shell(env);
	else
	{
		while (iter)
		{
			if ((ft_strcmp("SHLVL", iter->name))== 0)
			{
				if (ft_check_arg_is_num(iter->content) != 1)
					holder = 0;
				else
					holder = ft_atoll(iter->content);
				if (holder <= 0)
				{
					if (holder <= 0)
					{
						holder = -1;
					}
					else
						holder = 0;
				}
				holder += 1;
				if (holder > 1000)
				{
					errno_printer_3("warning: shell level","too high, resetting to 1", ft_itoa(holder), 0);
					holder = 1;
				}
				free(iter->content);
				iter->content = ft_itoa(holder);
				break;
			}
			iter = iter->next;
		}

	}
}

