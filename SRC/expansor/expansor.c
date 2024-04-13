/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:42:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/13 13:49:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*=======	WARNING, BE CAREFUL WHEN SPLEETING THIS FUNCTIONS	==========*/
/*	try (export value and echo $value) (echo $USER$?)  (echo $? $USER) 
echo $'?' echo $"?"*/

// CURRENTLY NOT WORKIN!!! echo "$USER $USER $USER" and so on, mess around 
//inside double quotes
//and apply fix to expand_str_extra
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
		return (NULL);
	env_cont = ft_strdup(iter->content);
	if (!env_cont)
		return (free(str), ft_strdup(""));
	result = trim_bef(str, '$');
	tmp = ft_strjoinplus(result, env_cont);
	free(env_cont);
	env_cont = trim_after(str, '$');
	result = ft_strjoinplus(tmp, env_cont);
	return (free(env_cont), free(str), result);
}

char	*get_env_name(char *str)
{
	int		x;
	char	*name;

	if (!str)
		return (NULL);
	x = 0;
	while (str[x] != '$' && (is_poss_char(str[x]) != 0) && str[x] != '\0')
		x++;
	name = malloc((x + 1) * sizeof(char));
	if (!name)
		return (NULL);
	x = 0;
	while (str[x] != '$' && (is_poss_char(str[x]) != 0) && str[x] != '\0')
	{
		name[x] = str[x];
		x++;
	}
	name[x] = '\0';
	return (name);
}

char	*dllr_support(char *result, t_env *env, int *x)
{
	char	*env_name;
	char	*tmp;
	char	*tmp2;
	char	*test1;

	env_name = get_env_name(&result[*x + 1]);
	if (env_exist(env, env_name) == true)
		result = expand_str(env_name, env, result);
	else
	{
		tmp = trim_bef(result, '$');
		test1 = trim_after(result, '$');
		free(result);
		tmp2 = ft_strjoinplus(tmp, test1);
		free(test1);
		result = ft_strdup(tmp2);
		free(tmp2);
	}
	*x = -1;
	free(env_name);
	return (result);
}

char	*fnd_dllr(char *str, t_env *env, int exit_code)
{
	int		x;
	char	*result;

	x = 0;
	if (!str)
		return (NULL);
	result = ft_strdup(str);
	free(str);
	if (!result)
		return (NULL);
	while (result[x] != '\0')
	{
		if (result[x] && result[x] == '$' && result[x + 1] == '?')
			result = expand_str_extra(result, exit_code, &x);
		else if (result[x] && result[x] == '$' && (is_poss_char(result[x + 1])
				!= 0) && result[x + 1] != '\0')
			result = dllr_support(result, env, &x);
		x++;
	}
	return (result);
}
