/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:21:01 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/06 16:56:39 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredock(t_parser *parser, t_env *env, int exit_code)
{
	t_parser *iter;
	t_redir *tmp;
	int		i;
	char *nl_h;
	char *filename;
	char	*num;
	int		fd;

	i = 0;
	iter = parser;
	while (iter)
	{
		tmp = iter->redir;
		if (tmp && tmp->dest)
		{
			if (tmp->sign == LESSLESS)
			{
				num = ft_itoa(i);
				filename = ft_strjoin("tmp/SRC/.hd", num);
				free (num);
				fd = -1;
				fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
				nl_h = readline("> ");
				while (nl_h && ft_strcmp(nl_h, tmp->dest) != 0)
				{
					nl_h = find_dollar(nl_h, env, exit_code);	//why will only expand once?
					nl_h = ft_strjoinplus(nl_h, "\n");
					ft_putstr_fd(nl_h, fd);
					free (nl_h);
					nl_h = readline("> ");
				}
				close (fd);
				free(nl_h);
			}
			i++;
			free(tmp->dest);
			tmp->dest = filename;
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

