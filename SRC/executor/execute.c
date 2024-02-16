/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:07:40 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/16 19:05:07 by adanylev         ###   ########.fr       */
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
	pipex.std_in = dup(STDIN_FILENO);
	pipex.std_out = dup(STDOUT_FILENO);
	env = env_to_char(envi);
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
	}
}

void	child_process(t_pipe *pipex, t_parser *parser, char **env)
{
	char	*cmd_path;
	
	fd_situation
	
}

void	fd_situation(t_pipe *pipex, t_parser *parser)
{
	if (!parser->next)
	 	dup2(pipex->fd[1], STDOUT_FILENO);
	
}











