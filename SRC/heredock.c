/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:21:01 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/03 08:12:36 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need a way to know the first word so i use it as a key to close the heredock.
//also i need a way to expand what im typing in the heredock.
//maybe instead of opening proper fd, create a tmp file to store the text?
int	heredock(t_parser *parser, t_env *env, int exit_code)
{
	int		i;
	int		pid;
	char	*line;
	(void)env;
	t_redir	*tmp;

	i = 0;
	tmp = parser->redir;
	while (tmp && tmp->dest)
	{
		if (tmp->sign == LESSLESS)
		{
			pipe(tmp->fd);
			pid = fork();
			if (pid == 0)
			{
				close(tmp->fd[0]);
				while (1)
				{
					line = readline("> ");
					if (!line)// need a way to know the first word so i use it as a key to close the heredock.
						break;
					write(tmp->fd[1], line, ft_strlen(line));
					write(tmp->fd[1], "\n", 1);
					free(line);
				}
				close(tmp->fd[1]);
				exit(0);
			}
			else
			{
				waitpid(pid, &exit_code, 0);
				close(tmp->fd[1]);
				dup2(tmp->fd[0], 0);
				close(tmp->fd[0]);
			}
		}
		tmp = tmp->next;
	}
	return (exit_code);
}
