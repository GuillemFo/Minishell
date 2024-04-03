/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:42:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/03 14:32:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str(char *name, t_env *env, char *str)
{
	t_env	*iter;
	char	*env_cont;
	char	*tmp;
	char	*result;

	iter = env;
	while (iter && ft_strcmp(name, iter->name) != 0)
		iter = iter->next;
	if (!iter)
	{
		result = ft_strdup(str);
		free(str);
		return (result);
	}
	env_cont = ft_strdup(iter->content);
	result = trim_bef(str, '$');
	tmp = ft_strjoini(result, env_cont);
	free(result);
	free(env_cont);
	env_cont = trim_after(str, '$');
	result = ft_strjoini(tmp, env_cont);
	free(env_cont);
	free(tmp);
	free(str);
	return (result);
}

char	*get_env_name(char *str)
{
	int		x;
	char	*name;

	if (!str)
		return (NULL);
	x = 0;
	while (str[x] != '$' && (is_poss_char(str[x]) == 1) && str[x] != '\0')
		x++;
	name = malloc((x + 1) * sizeof(char));
	if (!name)
		return (NULL);
	x = 0;
	while (str[x] != '$' && (is_poss_char(str[x]) == 1) && str[x] != '\0')
	{
		name[x] = str[x];
		x++;
	}
	name[x] = '\0';
	return (name);
}

char	*call_expansion(t_env *env, char *env_name, char *result)
{
	char	*tmp;
	char	*test1;
	char	*tmp2;
	char *tmp3;

	if (env_exist(env, env_name) == true)
		tmp3 = expand_str(env_name, env, result);
	else
	{
		test1 = trim_after(result, '$');
		tmp = trim_bef(result, '$');
		free(result);
		tmp2 = ft_strjoinplus(tmp, test1);
		free(test1);
		tmp3 = ft_strdup(tmp2);
		free(tmp2);
	}
	return (tmp3);
}

char	*find_dollar(char *str, t_env *env, int exit_code)
{
	int		x;
	char	*env_name;
	char	*result;
	char	*tmp;

	x = 0;
	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (free(str), NULL);
	while (result[x] != '\0')
	{
		result = find_dollar_var(result, exit_code);//leak
		if (result[x] && result[x] == '$' && (is_poss_char(result[x + 1]) != 0)
			&& result[x + 1] != '\0')
		{
			env_name = get_env_name(&result[x + 1]);
			result = call_expansion(env, env_name, result);
			free(env_name);
			x = -1;
		}
		x++;
	}
	free(str);
	return (result);
}
