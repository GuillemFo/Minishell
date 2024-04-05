/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:10 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/05 09:45:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errno_printer(char *com, char *error_txt, char *asked)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(asked, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_txt, 2);
	write(2, "\n", 1);
	return (0);
}

int	errno_printer_2(char *com, char *error_txt, char *asked, int val)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(asked, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_txt, 2);
	write(2, "\n", 1);
	return (val);
}

int	errno_printer_3(char *com, char *error_txt, char *asked, int val)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(" (", 2);
	ft_putstr_fd(asked, 2);
	ft_putstr_fd(") ", 2);
	ft_putstr_fd(error_txt, 2);
	write(2, "\n", 1);
	return (val);
}

int	errno_printer_home(char *com, char *asked)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(asked, 2);
	write(2, "\n", 1);
	return (0);
}

int	errno_printer_export(char *com, char *error_txt, char *asked)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(asked, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(error_txt, 2);
	write(2, "\n", 1);
	return (0);
}


char	*trim_bef(char *str, char c) 
{
    int i = 0;
	char *new_str;
	if (!str)
		return (NULL);
    while (str[i] != c && str[i] != '\0')
	{
        i++;
	}
	new_str = malloc((i + 1) * sizeof(char));
    if (!new_str)
        return NULL;
    ft_strncpy(new_str, str, i);
    new_str[i] = '\0';
    return (new_str);
}

char	*trim_support(char *str, char *new_str, int i, int x)
{
	if (str[i] == '?')
		i++;
	while (str[i] != '\0')
	{
		i++;
		x++;
	}
	free(new_str);
	new_str = my_malloc ((x + 1) * sizeof(char));
	i = i - x;
	x = 0;
	while (str[i] != '\0')
	{
		new_str[x] = str[i];
		x++;
		i++;
	}
	new_str[x] = '\0';
	return (new_str);
}

char *trim_after(char *str, char c)
{
	int i;
	int x;
	char *new_str;
	if (!str)
		return (NULL);
	i = 0;
	x = 0;
	new_str = ft_strdup("");	//porque da leaks? y porque si lo pong null no va nada mas? que depende de esta fucion?
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
	{
		i++;
		while (str[i] != '\0' && str[i] != c)
			i++;
		if (str[i] != '\0')
			new_str = trim_support(str, new_str, i , x);
	}
	return (new_str);
}
