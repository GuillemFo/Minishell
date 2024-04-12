/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:10 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/12 15:59:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_bef(char *str, char c)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != c && str[i] != '\0')
		i++;
	new_str = malloc((i + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, i);
	new_str[i] = '\0';
	return (new_str);
}

char	*trim_support(char *str, char *new_str, int *i, int x)
{
	if (str[*i] == '?')
		*i = *i +1;
	while (str[*i] != '\0')
	{
		*i = *i +1;
		x++;
	}
	new_str = my_malloc ((x + 1) * sizeof(char));
	*i = *i - x;
	x = 0;
	while (str[*i] != '\0')
	{
		new_str[x] = str[*i];
		x++;
		*i = *i +1;
	}
	new_str[x] = '\0';
	return (new_str);
}

char	*trim_after(char *str, char c)
{
	int		i;
	int		x;
	char	*new_str;

	if (!str)
		return (NULL);
	i = 0;
	x = 0;
	new_str = NULL;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
	{
		i++;
		while (is_poss_char(str[i]) != 0)
			i++;
		if (str[i] != '\0')
			new_str = trim_support(str, new_str, &i, x);
	}
	return (new_str);
}
