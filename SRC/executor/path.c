/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:12:44 by adanylev          #+#    #+#             */
/*   Updated: 2024/03/09 17:50:24 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	parse_path(char **envp, t_pipe *pipex)
{
	int		b;
	char	*tmp;

	b = 0;
	while (envp && *envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			b = 1;
			tmp = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
			pipex->paths = ft_split(tmp, ':');
			free(tmp);
			if (!pipex->paths)
				exec_error("Pipex: Memory issues\n");
		}
		envp++;
	}
}

char	*find_command(t_pipe *pipex, t_parser *parser)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (pipex->paths && pipex->paths[i] != NULL)
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		tmp2 = ft_strjoin(tmp, parser->cmd[0]);
		if (access(tmp2, X_OK) == 0)
		{
			free(tmp);
			return (tmp2);
		}
		free(tmp);
		free(tmp2);
		i++;
	}
	error_child(2, parser->cmd[0], 127);
	return (0);
}
