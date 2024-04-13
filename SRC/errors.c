/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:43:57 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 13:41:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	ft_error(int ernu, char *msg, int *error)
{
	write(2, "bash: ", 6);
	write(2, msg, ft_strlen(msg));
	if (ernu == 1)
	{
		write(2, ": Permission denied\n", 21);
		*error = 126;
	}
	else if (ernu == 2)
	{
		write(2, ": command not found\n", 21);
		*error = 127;
	}
	else if (ernu == 3)
	{
		write(2, ": No such file or directory\n", 29);
		*error = 1;
	}
}

int	error_child(int ernu, char *msg, int excode)
{
	write(2, "bash: ", 6);
	write(2, msg, ft_strlen(msg));
	if (ernu == 1)
		write(2, ": Permission denied\n", 21);
	else if (ernu == 2)
		write(2, ": command not found\n", 21);
	else if (ernu == 3)
		write(2, ": No such file or directory\n", 29);
	exit(excode);
}

void	ft_other_error(char *msg, int *error, int num)
{
	write(2, "bash: ", 6);
	write(2, msg, ft_strlen(msg));
	*error = num;
}

void	free_all(t_parser *data)
{
	if (data)
		free_parser(data);
}

int	errno_printer_quotes(char *com, char *error_txt, int val)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(error_txt, 2);
	write(2, "\n", 1);
	return (val);
}
