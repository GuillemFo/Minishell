/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:19:06 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 12:11:04 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	free_parent(t_pipe *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (pipex->children)
		free(pipex->children);
}

char	*ft_strjoini(char const *s1, char const *s2)
{
	size_t	i;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (*s1)
	{
		join[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		join[i] = *s2;
		i++;
		s2++;
	}
	join[i] = '\0';
	return (join);
}

int	is_builtin_or_not(t_parser *parser)
{
	if (parser->cmd[0])
	{
		if (ft_strncmp("echo", parser->cmd[0], 5) == 0)
			return (1);
		else if (ft_strncmp("cd", parser->cmd[0], 3) == 0)
			return (1);
		else if (ft_strncmp("pwd", parser->cmd[0], 4) == 0)
			return (1);
		else if (ft_strncmp("env", parser->cmd[0], 4) == 0)
			return (1);
		else if (ft_strncmp("exit", parser->cmd[0], 5) == 0)
			return (1);
		else if (ft_strncmp("export", parser->cmd[0], 7) == 0)
			return (1);
		else if (ft_strncmp("unset", parser->cmd[0], 6) == 0)
			return (1);
	}
	return (0);
}

void	exec_start(t_pipe *pipex, t_parser *parser)
{
	pipex->std_in = dup(STDIN_FILENO);
	pipex->std_out = dup(STDOUT_FILENO);
	pipex->num_cmds = parser_size(parser);
	pipex->children = my_malloc(sizeof(pid_t) * pipex->num_cmds);
	pipex->path = NULL;
	pipex->paths = NULL;
}

void	exec_finish(t_pipe *pipex)
{
	dup2(pipex->std_in, STDIN_FILENO);
	dup2(pipex->std_out, STDOUT_FILENO);
	close(pipex->std_in);
	close(pipex->std_out);
	free_parent(pipex);
}
