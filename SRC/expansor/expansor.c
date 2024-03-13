/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:42:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/13 14:43:17 by gforns-s         ###   ########.fr       */
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
	while (iter && iter->next && ft_strncmp(name, iter->name, ft_strlen(name)) != 0)
		iter = iter->next;
	if (!iter) // Check if iter is NULL
		return ft_strdup(str); // Return a copy of str if name is not found
	env_cont = ft_strdup(iter->content); // No need to allocate memory separately
	tmp = ft_strjoin(trim_bef(str, '$'), env_cont);
	result = ft_strjoin(tmp, trim_after(str, '$'));
	free(env_cont); // Free allocated memory
	free(tmp); // Free allocated memory
	return (result);
}

char	*get_env_name(char *str)
{
	int		x;
	char	*name;

	if (!str)
		return NULL;
	x = 0;
	while (str[x] != '$' && str[x] != ' ' && str[x] != '\'' && str[x] != '\0')
		x++;
	name = malloc((x + 1) * sizeof(char));
	if (!name)
		return (NULL);
	x = 0;
	while (str[x] != '$' && str[x] != ' ' && str[x] != '\'' && str[x] != '\0')
	{
		name[x] = str[x];
		x++;
	}
	name[x] = '\0';
	//printf("%s\n", name);
	return (name);
}

char	*find_dollar(char *str, t_env *env)
{
	int		x;
	char	*env_name;
	char	*result;
	char	*tmp;
	char *test1;

	x = 0;
	if (!str)
		return NULL;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (result[x] != '\0') // Correct the loop condition
	{
		if (result[x] == '$' && result[x + 1] != '\0')
		{
			env_name = get_env_name(&result[x + 1]);
			if (env_exist(env, env_name) == true)
			{
				result = expand_str(env_name, env, result); // Might be losing the data here. Readme line 132.
				x = 0;
			}
			else
			{
				test1 = trim_after(result, '$');
				tmp = trim_bef(result, '$');
				free(result); // Free allocated memory
				result = ft_strjoin(tmp, test1);
				free(tmp); // Free allocated memory
				x = 0;
			}
			free(env_name); // Free allocated memory
		}
		x++;
	}
	return (result);
}


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