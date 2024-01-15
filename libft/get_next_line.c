/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:50:07 by gforns-s          #+#    #+#             */
/*   Updated: 2023/10/25 19:13:35 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char	*ft_free(char *s1, char *s2)
{
	free (s1);
	free (s2);
	return (0);
}

char	*ft_left_tmp(char *tmp, char *line)
{
	char	*newtmp;
	int		i;
	int		j;

	if (!line)
		return (0);
	if (ft_strlen(tmp) - ft_strlen(line) == 0)
	{
		if (tmp)
			free (tmp);
		return (NULL);
	}
	newtmp = malloc (((ft_strlen(tmp) - ft_strlen(line)) + 1) * sizeof(char));
	if (!newtmp)
	{
		free (tmp);
		return (0);
	}
	i = ft_strlen(line);
	j = 0;
	while (tmp[i] != '\0')
		newtmp[j++] = tmp[i++];
	newtmp[j] = '\0';
	free (tmp);
	return (newtmp);
}

char	*ft_create_line(char *tmp)
{
	char	*line;
	int		i;

	if (!tmp)
		return (0);
	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	if (tmp[i] == '\n')
		line = malloc ((i + 2) * sizeof(char));
	else
		line = malloc ((i + 1) * sizeof(char));
	if (!line)
		return (0);
	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
	{
		line[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_readline(char *tmp, int fd)
{
	int		rdbytes;
	char	*buff;

	rdbytes = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
	{
		free(tmp);
		return (0);
	}
	while (rdbytes > 0 && ft_strchrplus(tmp, '\n') == 0)
	{
		rdbytes = read (fd, buff, BUFFER_SIZE);
		if (rdbytes == -1)
			return (ft_free(tmp, buff));
		else if (rdbytes > 0)
		{
			buff[rdbytes] = '\0';
			tmp = ft_strjoinplus(tmp, buff);
			if (!tmp)
				return (0);
		}
	}
	free (buff);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*tmp = NULL;
	char		*line;

	tmp = ft_readline(tmp, fd);
	if (!tmp)
		return (0);
	line = ft_create_line(tmp);
	if (!line)
	{
		free (tmp);
		tmp = NULL;
	}
	else
		tmp = ft_left_tmp(tmp, line);
	return (line);
}

/*
int	main(void)
{
	int		m;
	int		fd;
	char	*path;

	m = 0;
	path = "test.txt";
	fd = open(path, O_RDONLY);
	char *linea = get_next_line(fd);
	while (linea)
	{
		printf("-%s-", linea);
		free(linea);
		linea = get_next_line(fd);
	}
}*/