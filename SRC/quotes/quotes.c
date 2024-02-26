/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/26 18:43:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	has_quotes(char *str)
{
	int	i;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (str[i]);
		i++;
	}
	return (str[i]);
}


//Need to loop this for every time it encounters quotes!!
char	*clear_quotes(char *str)
{
	int		i;
	char	c;
	char 	*cpy;
	char	*tmp;

	i = 0;
	cpy = ft_strdup(str);
	c = has_quotes(cpy);
	printf("C=%c:\n", c);
	if (c != '\0')
	{
		while (cpy[i] != c)
			i++;
		tmp = malloc(i + 1 *sizeof(char));
		i = 0;
		while (cpy[i] != c)
		{
			tmp[i] = cpy[i];
			i++;
		}
		tmp[i] = '\0';
		i++;
		write(1, &cpy[i], 1);
		
		
		
	}
	else
		return (cpy);
	return (str);
}
