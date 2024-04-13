/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:36:16 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/12 15:24:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env_has_equal(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	if (var[i] == '=')
		return (true);
	return (false);
}

int	is_poss_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

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

char	*get_home(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->name, "HOME") == 0)
			return (iter->content);
		iter = iter->next;
	}
	return (NULL);
}
