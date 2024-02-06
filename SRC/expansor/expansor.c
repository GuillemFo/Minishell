/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:42:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/06 11:15:28 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

expand_str(char *str, t_env *env)
{
	int x;
	int	nm_len;
	int i;
	char *name;
	char *content_str;
	i = 0;
	x = 0;
	while (str[x]  != '$')
		x++;
	x++;
	while (str[x] != ' ' || str[x] != '\0')
	{
		x++;
		nm_len++;
	}
	name = malloc((nm_len +1) * sizeof(char));
	x -= nm_len;
	while (str[x] < nm_len)
	{
		name[i] = str[x];
		i++;
		x++;
	}
	name[i] = '\0';
	if (env_exist_2(env, name) == true)
		content_str = ft_env_content(env, name);
	
}


void	find_dollar(char *str, t_env *env)
{
	int	x;

	x = 0;
	while (str)
	{
		if (str[x] == '$')
			expand_str(str, env);
		x++;
	}

}