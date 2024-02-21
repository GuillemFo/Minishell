/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:07:40 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/21 12:32:00 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	execute(t_parser *parser, t_env	*envi)
{
	t_pipe	pipex;
	int	status;
	int	i;
	char	**env;
	
	i = 0;
	// here to check if there is oly one command and it is a built in; if yes - no fork needed, just execute and bye
		
	pipex.std_in = dup(STDIN_FILENO);
	pipex.std_out = dup(STDOUT_FILENO);
	env = env_to_char(envi);
	parse_path(env, &pipex);
	pipex.num_cmds = parser_size(parser);
	pipex.children = my_malloc(sizeof(pid_t) * pipex.num_cmds);
	while (parser)
	{
		if (pipe(pipex.fd) == -1)
			exec_error("Error: pipe\n");
		pipex.children[i] = fork();
		if (pipex.children[i] < 0)
			exec_error("Error: fork\n");
		if (pipex.children[i] == 0)
			child_process(&pipex, parser, env);
		dup2(pipex.fd[0], STDIN_FILENO);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		i++;
		parser = parser->next;
	}
}

void	child_process(t_pipe *pipex, t_parser *parser, char **env)
{
	fd_situation(pipex, parser);
	if (ft_strchr(parser->cmd[0], '/'))
	{
		if (access(parser->cmd[0], R_OK) >= 0)
			pipex->path = parser->cmd[0];
		else
			exec_error("Error: No path found\n");
	}
	else
		pipex->path = find_command(pipex);
	if (parser->redir)
	{
		
	}
	if (access(pipex->path, X_OK) >= 0)
		execve(pipex->path, parser->cmd, env);
	exec_error("Error: execution error\n");
}

void	fd_situation(t_pipe *pipex, t_parser *parser)
{
	if (parser->next)
		dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}











