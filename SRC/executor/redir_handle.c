/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:34:29 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/24 16:20:58 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	redir_manager(t_parser *parser)
{
	int	f;

	f = find_last_redir(parser->redir);
	if (f < 0)
		exec_error("Error: problem with the file\n");
	if (parser->redir->sign == 2 || parser->redir->sign == 4)
        dup2(f, STDOUT_FILENO);
	if (parser->redir->sign == 3 || parser->redir->sign == 5)
		dup2(f, STDIN_FILENO);
    close(f);
}


int find_last_redir(t_redir *redir) 
{
    int fd;
	
	fd = -1;
    while (redir != NULL) 
	{
        if (redir->sign == 2 || redir->sign == 4) {
            if (redir->dest != NULL) 
			{
                fd = open(redir->dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                    return (-1);
            }
        } 
		else if (redir->sign == 3 || redir->sign == 5) 
		{
            if (redir->dest != NULL)
			{
                fd = open(redir->dest, O_RDONLY);
                if (fd == -1)
                    return (-1);
            }
        }
        redir = redir->next;
    }
    return (fd);
}


