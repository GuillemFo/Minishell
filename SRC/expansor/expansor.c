/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:42:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/03 08:34:56 by gforns-s         ###   ########.fr       */
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
		return (str);
	env_cont = ft_strdup(iter->content);
	tmp = ft_strjoini(trim_bef(str, '$'), env_cont);
	result = ft_strjoini(tmp, trim_after(str, '$'));
	free(env_cont);
	free(tmp);
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
	char	*tmp2;
	char	*test1;

	if (env_exist(env, env_name) == true)
		result = expand_str(env_name, env, result);
	else
	{
		test1 = trim_after(result, '$');
		tmp = trim_bef(result, '$');
		free(result);
		tmp2 = ft_strjoinplus(tmp, test1);
		free(test1);
		result = ft_strdup(tmp2);
		free(tmp2);
	}
	return (result);
}

char	*find_dollar(char *str, t_env *env, int exit_code)
{
	int		x;
	char	*env_name;
	char	*result;

	x = 0;
	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (result[x] != '\0')
	{
		result = find_dollar_var(result, exit_code);
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
	return (result);
}
