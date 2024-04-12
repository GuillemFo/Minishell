/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:54:42 by codespace         #+#    #+#             */
/*   Updated: 2024/04/12 15:55:01 by codespace        ###   ########.fr       */
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
