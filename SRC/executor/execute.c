/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:07:40 by adanylev          #+#    #+#             */
/*   Updated: 2024/03/12 12:28:09 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	execute(t_parser *parser, t_env **envi, int *error)
{
	t_pipe	pipex;
	int		status;

	if (!parser)
		return (0);
	if (parser->cmd)
	{
		if (is_builtin_or_not(parser) && !parser->next)
			is_lonely_builtin(parser, &pipex, envi);
		else
		{
		exec_start(&pipex, parser);
		making_kids(parser, &pipex, envi, error);
		waiting(&pipex, &status, pipex.num_cmds);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));}
	}
	return (1);
}

void	child_process(t_pipe *pipex, t_parser *parser, t_env **envi, int *error)
{
	char	**env;

	env = NULL;
	fd_situation(pipex, parser);
	env = env_to_char(*envi);
	parse_path(env, pipex);
	if (parser->cmd && ft_strchr(parser->cmd[0], '/'))
	{
		if (access(parser->cmd[0], R_OK) >= 0)
			pipex->path = parser->cmd[0];
		else
		{
			ft_other_error("Error: No path found\n", error, 1);
			exit(1);
		}
	}
	if (parser->redir)
		redir_manager(parser);
	if (parser->cmd && is_builtin_or_not(parser) == 1)
		exit(is_builtin_execute(parser, envi));
	else if (parser->cmd && !pipex->path)
		pipex->path = find_command(pipex, parser);
	if (parser->cmd && access(pipex->path, X_OK) >= 0)
		execve(pipex->path, parser->cmd, env);
	execute_fin(parser);
}

void	fd_situation(t_pipe *pipex, t_parser *parser)
{
	if (parser->next)
		dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	is_lonely_builtin(t_parser *parser, t_pipe *pipex, t_env **envi)
{
	int	i;

	i = 1;
	pipex->std_in = dup(STDIN_FILENO);
	pipex->std_out = dup(STDOUT_FILENO);
	redir_manager(parser);
	i = is_builtin_execute(parser, envi);
	dup2(pipex->std_in, STDIN_FILENO);
	dup2(pipex->std_out, STDOUT_FILENO);
	return (i);
}

void	making_kids(t_parser *parser, t_pipe *pipex, t_env **envi, int *error)
{
	int	i;

	i = 0;
	while (parser)
	{
		if (pipe(pipex->fd) == -1)
			exec_error("Error: pipe\n");
		pipex->children[i] = fork();
		if (pipex->children[i] < 0)
			exec_error("Error: fork\n");
		if (pipex->children[i] == 0)
			child_process(pipex, parser, envi, error);
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		i++;
		parser = parser->next;
	}
}
