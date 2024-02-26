/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:19:06 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/24 15:22:09 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	free_parent(t_pipe *pipex)
{
	int	i;

	i = 0;
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (pipex->children)
		free(pipex->children);
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	if (pipex->path)
		free(pipex->path);
}