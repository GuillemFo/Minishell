/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:15:28 by codespace         #+#    #+#             */
/*   Updated: 2024/04/12 14:17:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**get_old_pwd(t_env **env)
{
	t_env	*iter;
	char	*tmp;

	tmp = getcwd(NULL, MAXPATHLEN);
	iter = *env;
	while (iter->next && ft_strncmp(iter->name, "OLDPWD", 7) != 0)
		iter = iter->next;
	if (iter->name != NULL && ft_strncmp(iter->name, "OLDPWD", 7) == 0)
	{
		if (tmp != NULL)
		{
			free (iter->content);
			iter->content = tmp;
			iter->is_hidden = false;
		}
	}
	else if (!iter->next && tmp)
	{
		iter->next = malloc(sizeof(t_env));
		iter->next->name = ft_strdup("OLDPWD");
		iter->next->content = tmp;
		iter->next->is_hidden = false;
		iter->next->next = NULL;
	}
	return (env);
}

t_env	**get_pwd(t_env **env)
{
	t_env	*iter;
	char	*tmp;

	tmp = getcwd(NULL, MAXPATHLEN);
	iter = *env;
	while (iter->next && ft_strncmp(iter->name, "PWD", 4) != 0)
		iter = iter->next;
	if (iter->name != NULL && ft_strncmp(iter->name, "PWD", 4) == 0)
	{
		free (iter->content);
		iter->content = tmp;
		iter->is_hidden = false;
	}
	else if (!iter->next && tmp)
	{
		iter->next = malloc(sizeof(t_env));
		iter->next->name = ft_strdup("PWD");
		iter->next->content = tmp;
		iter->next->is_hidden = false;
		iter->next->next = NULL;
	}
	return (env);
}

int	built_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, MAXPATHLEN);
	ft_printf("%s\n", tmp);
	free (tmp);
	return (0);
}

int	check_is_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		while (str[i] == '-' && str[i + 1] == 'n')
			i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (i);
		else
			return (0);
	}
	return (i);
}
