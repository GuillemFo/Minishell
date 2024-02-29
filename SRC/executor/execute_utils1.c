/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:19:06 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/29 15:26:39 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	free_parent(t_pipe *pipex)
{
	int	i;

	i = 0;
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (pipex->children)
		free(pipex->children);
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
}
char	*ft_strjoini(char const *s1, char const *s2)
{
	size_t	i;
	char	*join;
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
