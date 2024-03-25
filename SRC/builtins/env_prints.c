/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:30:47 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/25 16:31:13 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this works fine
int	print_hidden_lst(t_env *env)
{
	t_env	*iter;
	
	iter = env;
	while (iter != NULL)
	{	if (iter->is_hidden == false)
			ft_printf("declare -x %s=\"%s\"\n", iter->name, iter->content);
	else if (iter->is_hidden == true)
		ft_printf("declare -x %s\n", iter->name, iter->content);
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