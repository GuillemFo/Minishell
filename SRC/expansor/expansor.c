/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:42:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/15 12:25:46 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str(char *name, t_env *env, char *str)
{
	char	*result;
	t_env	*iter;
	char	*env_cont;
	char	*tmp;
	int		len;

	iter = env;
	len = ft_strlen(name);
	while (iter->next && ft_strncmp(name, iter->name, len) != 0)
		iter = iter->next;
	len = ft_strlen(iter->content);
	env_cont = malloc((len + 1) * sizeof(char));
	if (!env_cont)
		return (NULL);
	env_cont = ft_strdup(iter->content);
	tmp = ft_strjoin(trim_bef(str, '$'), env_cont);
	result = ft_strjoin(tmp, trim_after(str, '$'));
	return (result);
}

char	*get_env_name(char *str)
{
	int		x;
	char	*name;

	x = 0;
	while (str[x] != ' ' && str[x] != '\0')
		x++;
	name = malloc((x + 1) * sizeof(char));
	if (!name)
		return (NULL);
	x = 0;
	while (str[x] != ' ' && str[x] != '\0')
	{
		name[x] = str[x];
		x++;
	}
	name[x] = '\0';
	return (name);
}

char	*find_dollar(char *str, t_env *env)
{
	int		x;
	char	*env_name;
	char	*result;

	x = 0;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (result[x] != '\0')
	{
		if (result[x] == '$' && result[x + 1] != '\0')
		{
			env_name = get_env_name(&result[x + 1]);
			if (env_exist(env, env_name) == true)
				result = expand_str(env_name, env, result);
		}
		x++;
	}
	return (result);
}
