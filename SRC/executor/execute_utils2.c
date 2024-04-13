/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:08:51 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 12:11:47 by adanylev         ###   ########.fr       */
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

void	execute_fin(t_parser *parser)
{
	if (parser->cmd)
		error_child(1, parser->cmd[0], 126);
	exit(1);
}

int	status_situation(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		else if (WTERMSIG(status) == SIGQUIT)
		{
			return (131);
			ft_printf("Quit: 3\n");
		}
	}
	return (status);
}
