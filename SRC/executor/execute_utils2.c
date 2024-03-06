/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:08:51 by adanylev          #+#    #+#             */
/*   Updated: 2024/03/06 14:12:24 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	waiting(t_pipe *pipex, int *status, int num_cmds)
{
	int	i;
	
	i = 0;
	while (i < num_cmds)
	{
		waitpid(-1, status, 0);
		i++;
	}
	exec_finish(pipex);
}