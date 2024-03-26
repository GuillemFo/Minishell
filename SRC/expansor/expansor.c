/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:42:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/26 07:50:21 by gforns-s         ###   ########.fr       */
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
		return (ft_strdup(str));
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
		return NULL;
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

char	*find_dollar(char *str, t_env *env, int exit_code)
{
	int		x;
	char	*env_name;
	char	*result;
	char	*tmp;
	char	*tmp2;
	char *test1;

	x = 0;
	if (!str)
		return NULL;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	result = find_dollar_var(result, exit_code);
	while (result[x]!= '\0')
	{
		if (result[x] && result[x] == '$' && (is_poss_char(result[x + 1]) != 0) && result[x + 1] != '\0')
		{
			env_name = get_env_name(&result[x + 1]);
			if (env_exist(env, env_name) == true)
			{
				result = expand_str(env_name, env, result); // Might be losing the data here. Readme line 132.
				x = -1;
			}
			else
			{
				test1 = trim_after(result, '$');
				tmp = trim_bef(result, '$');
				tmp2 = ft_strjoinplus(tmp, test1);
				result = ft_strdup(tmp2);
				free(tmp);
				free(test1);
				free(tmp2);
				x = -1;
			}
			free(env_name);
		}
		x++;
	}
	return (result);
}


//im scared to delete this part because it might be useful at some point

// looking at it and the tools for trimming
// char	*expand_str(char *name, t_env *env, char *str)
// {
	// t_env	*iter;
	// int		len;
	// char	*env_cont;
	// char	*tmp;
	// char	*result;
// 
	// iter = env;
	// len = ft_strlen(name);
	// while (iter->next && ft_strncmp(name, iter->name, len) != 0)
		// iter = iter->next;
	// len = ft_strlen(iter->content);
	// env_cont = malloc((len + 1) * sizeof(char));
	// if (!env_cont)
		// return (NULL);
	// env_cont = ft_strdup(iter->content);
	// tmp = ft_strjoin(trim_bef(str, '$'), env_cont);
	// result = ft_strjoin(tmp, trim_after(str, '$'));
	// return (result);
// }
// 
// char	*get_env_name(char *str)
// {
	// int		x;
	// char	*name;
// 
	// x = 0;
	// while (str[x] != '$' && str[x] != ' ' && str[x] != '\0')
		// x++;
	// name = malloc((x + 1) * sizeof(char));
	// if (!name)
		// return (NULL);
	// x = 0;
	// while (str[x] != '$' && str[x] != ' ' && str[x] != '\0')
	// {
		// name[x] = str[x];
		// x++;
	// }
	// name[x] = '\0';
	// return (name);
// }
// 
// char	*find_dollar(char *str, t_env *env)
// {
	// int		x;
	// char	*env_name;
	// char	*result;
	// char	*tmp;
	// int	test=0;
	// int	test2=0;
// 
	// x = 0;
	// result = ft_strdup(str);
	// if (!result)
		// return (NULL);
	// if (result[x] != '\0')
	// {
		// while (result[x] != '\0')
		// {
			// if (result[x] == '$' && result[x + 1] != '\0')
			// {
				// env_name = get_env_name(&result[x + 1]);
				// if (env_exist(env, env_name) == true)
				// {
					// result = expand_str(env_name, env, result);
					// x = 0;
				// }
				// else
				// {
					// printf("TEST: %d\n", ++test);
					// tmp = trim_bef(result, '$');
					// result = ft_strjoin(tmp, trim_after(result, '$'));
					// printf("TEST2: %d\n", ++test2);
				// }
			// }
			// x++;
				// printf("TEST2: %d\n", ++test2);
		// }
	// }
	// return (result);
// }
// 