/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:21:01 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/17 10:21:08 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_heredock(char *path, char *where) // what else???
{
	int fd;
	char *str;
	// so i saved a fd[2] for io and now i cant access ... better build new one so no mallocs involved 
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	str = readline("> ");
	while (str && ft_strcmp(where, str) != 0)
	{
		str = ft_strjoini(str, "\n");
		ft_putstr_fd(str, fd);
		free(str);
		str = readline("> ");
	}
	close(fd);
	free(str);
	return (0); //signals??
}

int	start_heredock(t_redir *sup,int i)
{
	char	*path;
	char 	*num;

	num = ft_itoa(i);
	path = ft_strjoini("/tmp/cache", num);
	//free(numb);	issues???
	build_heredock(path, sup->dest);
	//free(sup->dest); really needed?
	sup->dest = ft_strdup(path);
	//free??
	return (0);//what returns?
}


int	heredock_check(t_parser	*parser)
{
	t_redir *sup;
	int	i;

	i = 0;
	while (parser->redir)
	{
			sup = parser->redir;
		while (sup->sign)
		{
			if (sup->sign == LESSLESS)
			{
				start_heredock(sup, i);
				i++;
			}
			sup = sup->next;
		}
		sup = sup->next;
	}
	return (1);  //what returns?
}