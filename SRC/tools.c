/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:10 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/19 09:28:20 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errno_printer(char *com, char *error_txt, char *asked)
{
	ft_putstr_fd("Minishell:", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(error_txt, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(asked, 2);
	write(2, "\n", 1);
	return (0);
}

// 19.02.24 09.28am 
// char	*clear_dollar(t_env *env, char *str)
// {
	// int	i;
	// int	j;
	// char *result;
// 
	// i = 0;
	// while (str[i] != '\0' && str[i] != '$')
		// i++;
	// if (str[i] != '\0')
	// {
		// i++;
		// if (env_exist(env, str[i]) == false)
		// {
			// j = i;
			// while (str[j] != '$' && str[j] != ' ' && str[j] != '\0')
		// }
	// 
// 
// }

char *trim_bef(char *str, char c)
{
	int	i;
	i = 0;
	char *new_str;
	new_str = ft_strdup(str);
	if (str[i] != c && str[i] != '\0')
	{
		while (str[i] != c && str[i] != '\0')
			i++;
		new_str = malloc((i + 1) * sizeof(char));
		if (!new_str)
			return (NULL);
		i = 0;
		while (str[i] != c)
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}

char *trim_after(char *str, char c)
{
	int i;
	int x;
	char *new_str;

	i = 0;
	x = 0;
	new_str = ft_strdup("");
	while (str[i] != c)
	{
		i++;
	}
	if (str[i] == '$')
	{
		i++;
		while (str[i] != c && str[i] != ' ' && str[i] != '\0')
			i++;
		if (str[i] != '\0')
		{
			while (str[i] != '\0')
			{
				i++;
				x++;
			}
			new_str = malloc ((x + 1) * sizeof(char));
			if (!new_str)
				return (NULL);
			i = i - x;
			x = 0;
			while (str[i] != '\0')
			{
				new_str[x] = str[i];
				x++;
				i++;
			}
			new_str[x] = '\0';
		}
	}
	return (new_str);
}

