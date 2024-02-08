/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:42:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/08 11:01:13 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str(char *name, t_env *env, char *str)
{
	char 	*result;
	t_env 	*iter;
	char 	*env_cont;
	char	*tmp;
	int		cnt_len;

	iter = env;
	printf("===============================\n");
	while (iter->next && ft_strcmp(name, iter->next->content) != 0)
		iter = iter->next;
	cnt_len = ft_strlen(iter->content);
	env_cont = malloc((cnt_len + 1) * sizeof(char));
	if (!env_cont)
		return (NULL);
	tmp = ft_strjoin(trim_bef(str, '$'), env_cont);
	result = ft_strjoin(tmp, trim_after(str, '$'));
	return (result);
}

char	*get_env_name(char *str)
{
	int	x;
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
	int	x;
	char *env_name;
	char *result;

	x = 0;
	result = ft_strdup(str);
	while (str[x] != '\0')
	{
		if (str[x] == '$' && str[x + 1] != '\0')
		{
			env_name = get_env_name(&str[x + 1]);
			if (env_exist(env, env_name) == true)
				result = expand_str(env_name, env, str);
			else
				result = ft_strjoin(trim_bef(str, '$'), trim_after(str, '$'));
		}
		x++;
	}
	return (result);
}
