/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:21:01 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/28 02:13:32 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredock(t_parser *parser, t_env *env, int exit_code)
{
	int		fd[2];
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
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				while (1)
				{
					line = readline("> ");
					if (!line)
						break ;
					write(fd[1], line, ft_strlen(line));
					write(fd[1], "\n", 1);
					free(line);
				}
				close(fd[1]);
				exit(0);
			}
			else
			{
				waitpid(pid, &exit_code, 0);
				close(fd[1]);
				dup2(fd[0], 0);
				close(fd[0]);
			}
		}
		tmp = tmp->next;
	}
	return (exit_code);
}
