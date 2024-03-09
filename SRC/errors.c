/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:43:57 by adanylev          #+#    #+#             */
/*   Updated: 2024/03/09 17:25:43 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	ft_error(int ernu, char *msg, int *error)
{
	if (ernu == 1)
	{
		write(2, "bash: ", 6);
		write(2, msg, ft_strlen(msg));
		write(2, ": Permission denied\n", 21);
		*error = 126;
	}
	else if (ernu == 2)
	{
		write(2, "bash: ", 6);
		write(2, msg, ft_strlen(msg));
		write(2, ": command not found\n", 21);
		*error = 127;
	}
	else if (ernu == 3)
	{
		write(2, "bash: ", 6);
		write(2, msg, ft_strlen(msg));
		write(2, ": No such file or directory\n", 29);
		*error = 1;
	}
}
int	error_child(int ernu, char *msg, int excode)
{
	if (ernu == 1)
	{
		write(2, "bash: ", 6);
		write(2, msg, ft_strlen(msg));
		write(2, ": Permission denied\n", 21);
	}
	else if (ernu == 2)
	{
		write(2, "bash: ", 6);
		write(2, msg, ft_strlen(msg));
		write(2, ": command not found\n", 21);
	}
	else if (ernu == 3)
	{
		write(2, "bash: ", 6);
		write(2, msg, ft_strlen(msg));
		write(2, ": No such file or directory\n", 29);
	}
	exit(excode);
}

void	ft_other_error(char *msg, int *error, int num)
{
	write(2, "bash: ", 6);
	write(2, msg, ft_strlen(msg));
	*error = num;
}

void	free_all(t_parser *data, char **str)
{
	if (data)
		free_parser(data);
	if (*str)
		free(*str);
	*str = readline(C_G "minishell: " C_RESET);
}
