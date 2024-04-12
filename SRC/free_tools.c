/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:44:25 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/12 16:31:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
	return (NULL);
}

void	*ft_free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

void	two_free(void *one, void *two)
{
	free(one);
	free(two);
}

void	three_free(void *one, void *two, void *three)
{
	free(one);
	free(two);
	free(three);
}
