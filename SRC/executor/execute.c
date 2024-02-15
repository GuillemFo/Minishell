/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:07:40 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/15 14:42:27 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	execute(t_parser *parser, t_env	*env)
{
	t_pipe	pipex;
	int	status;
	int	i;
	char	**env;
	
	i = 0;
	pipex.num_cmds = parser_size(parser);
	pipex.children = my_malloc(sizeof(pid_t) * pipex.num_cmds);
	if (pipe(pipex.fd) == -1)
		exec_error("Error: pipe\n");
	while (parser)
	{
		pipex.children[i] = fork();
		if (pipex.children[i] < 0)
			exec_error("Error: fork\n");
		if (pipex.children[i] == 0)
			child_process(pipex, parser, env);
			
	}
		

	
}

