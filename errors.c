/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:43:57 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/26 14:44:19 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	error(int ernu, char *msg, int excode)
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
	return (excode);
}