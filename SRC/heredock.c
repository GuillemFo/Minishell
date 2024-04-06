/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:21:01 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/06 15:53:44 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
open
close


key word
*/
int	heredock(t_parser *parser)
{
	t_parser *iter;
	t_redir *tmp;
	int		i;
	char *nl_h;
	char *filename;

	i = 0;
	iter = parser;
	while (iter)
	{
		tmp = iter->redir;
		if (tmp && tmp->dest)
		{

			//call do_heredock function.
			
			if (tmp->sign == LESSLESS)
			{
				filename = ft_strjoin(, );
				tmp->fd[i] = -1;
				tmp->fd[i] = open(tmp->dest, O_CREAT | O_WRONLY | O_TRUNC, 0666));	//which one ??
				//printf("#%s#\n", tmp->dest);
				while (1)
				{
					nl_h = readline("> ");
					//ft_printf("%s\n", nl_h);
					if (ft_strcmp(nl_h, tmp->dest) == 0)
						break;
					//printf fd?? but need to expand??
					nl_h = ft_strjoin(nl_h, "\n");
					ft_putstr_fd(nl_h, tmp->fd[i]);
					free (nl_h);
				}
				close (tmp->fd[i]);
			}
			i++;
			//tmp = tmp->next;
		}
		iter = iter->next;
	}
	return (999);
}

/*
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
			open(tmp->dest, tmp->fd[0]);
			open(tmp->dest, tmp->fd[1]);
			pipe(tmp->fd);
			pid = fork();
			if (pid == 0)
			{
				close(tmp->fd[0]);
				while (1)
				{
					line = readline("> ");
					if (ft_strcmp(line, tmp->dest) == 0)// need a way to know the first word so i use it as a key to close the heredock.
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
*/

