/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:10 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/19 12:14:50 by gforns-s         ###   ########.fr       */
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
	if (str[i] == c)
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

char	*cont_extract(char *str, char c)
{
	int	i;
	char *result;
	
	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		//write(1, &str[i], 1);
		i++;
	}
	result = malloc ((i + 1) * sizeof(char));
	ft_strlcpy(result,str, i);
	result[i] = '\0';
	return (result);
}

char	*quotes_pain(char *str)
{
	char *tmp;
	char *result;
	int	i;

	i = 0;
	result = ft_strdup(str);
	while (result[i] != '\0')
	{
		if (result[i] == '\"')
		{
			i++;
			write(1, &result[i], 1);
			tmp = cont_extract(result, '\"');
			result = ft_strdup(tmp);
			i = -1;
		}
		// else if (str[i] == 27)
		// {
			// i++;
			// tmp = trim_bef(result, 27);
			// result = ft_strjoin(tmp, trim_after(result, 27));
			// i = -1;
		// }
		i++;
	}
	return (result);
}
