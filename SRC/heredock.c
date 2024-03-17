/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:21:01 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/17 08:40:37 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_heredock(char *path, char *where) // what else???


int	start_heredock(t_redir *sup,int i)
{
	char	*path;
	char 	*num;

	num = ft_itoa(i);
	path = ft_strjoini("/tmp/cache", num);
	//free(numb);	issues???
	build_heredock(path, sup->dest);
	
}





int	heredock_check(t_redir *redir)
{
	t_redir *sup;
	int	i;

	i = 0;
	while (redir)
	{
		sup = redir;
		while (sup)
		{
			if (sup->sign == LESSLESS)
			{
				start_heredock(sup, i);
				i++;
			}
			sup = sup->next;
		}
		redir = redir->next;
	}
	return (1);
}