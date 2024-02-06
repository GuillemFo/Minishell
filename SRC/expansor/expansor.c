/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:42:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/06 13:24:28 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*THIS FUNCTION IS PURE TRASH AND I HAVE TO REDO IT */
char *expand_str(char *str, t_env *env)
{
	int x;
	int	i;
	char *name;
	char *content_str;
	char *tmp1;
	char *tmp2;
	char *help;
	content_str = NULL;
	tmp1 = NULL;
	x = 0;
	i = 0;
	while (str[x] != '$' && str[x] != '\0')
		x++;
	x++;
	while (str[x] != '\0' && str[x] != ' ')
	{
		x++;
		i++;
	}
	name = malloc((i +1) * sizeof(char));
	if (!name)
		return (NULL);
	x -= i;
	i = 0;
	while (str[x] != '\0' && str[x] != ' ')
	{
		name[i] = str[x];
		i++;
		x++;
	}
	name[i] = '\0';
	help = env_exist_2(env, name);
	if (help[0] != '\0')
	{
		content_str = env_exist_2(env, name);
		tmp1 = ft_strjoinplus(trim_bef(str, '$'), content_str);
		tmp2 = ft_strjoinplus(tmp1, trim_after(str, '$'));
		free(content_str);
	}
	else
		tmp2 = ft_strjoin(trim_bef(str, '$'), trim_after(str, '$'));
	return (tmp2);
}


char	*find_dollar(char *str, t_env *env)
{
	int	x;
	char *new_str;

	x = 0;
	while (str[x])
	{
		new_str = expand_str(str, env);
		x++;
	}
	return (new_str);
}