/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:34:19 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/25 10:18:37 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
t_env	*del_env()
{
	

}

t_env	*add_env()
{

}
*/

t_env	*load_env(char **envp)
{
	t_env		*env;
	int	y;
	
	y = 0;
	env = malloc(sizeof(t_env));
	while (envp[y] != NULL)
	{
		ft_printf("%s\n", envp[y]);
		y++;
	}

	return (env);
}

