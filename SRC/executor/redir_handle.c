/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:34:29 by adanylev          #+#    #+#             */
/*   Updated: 2024/03/02 19:15:48 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	redir_manager(t_parser *parser)
{
    int f;

	if (parser->redir->sign == 2 || parser->redir->sign == 4)
     {
        f = find_last_redir_out(parser->redir);
        if (f < 0)
		    exec_error("Error: problem with the file\n");
        dup2(f, STDOUT_FILENO);
     }
	if (parser->redir->sign == 3 || parser->redir->sign == 5)
	{
        f = find_last_redir_in(parser->redir);
        if (f < 0)
		    exec_error("Error: problem with the file\n");
        dup2(f, STDIN_FILENO);
    }
    close(f);
}


int find_last_redir_out(t_redir *redir) 
{
    int fd;
	
	fd = -1;
    while (redir != NULL) 
	{
        if ((redir->sign == 2 || redir->sign == 4) && redir->dest != NULL) 
        {
            if (redir->sign == 2)
                fd = open(redir->dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else
                fd = open(redir->dest, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (-1);
        }
        redir = redir->next;
    }
    return (fd);
}

int		find_last_redir_in(t_redir *redir)
{
    int fd;
	
	fd = -1;
    while (redir != NULL) 
	{
        if ((redir->sign == 3 || redir->sign == 5) && redir->dest != NULL) 
		{
            fd = open(redir->dest, O_RDONLY);
            if (fd == -1)
                return (-1);
        }
        redir = redir->next;
    }
    return (fd);
}
