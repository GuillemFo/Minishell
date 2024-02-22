/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:34:29 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/22 15:19:08 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	redir_manager(t_parser *parser)
{
	int	f;

	printf("lalala\n");
	f = find_last_redir(parser->redir);
	if (f < 0)
		exec_error("Error: problem with the file\n");
	if (parser->redir->sign == 2 || parser->redir->sign == 4)
		dup2(f, STDOUT_FILENO);
	if (parser->redir->sign == 3 || parser->redir->sign == 5)
		dup2(f, STDIN_FILENO);
	
}

int	find_last_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->sign == 2 || redir->sign == 4)
	{
		while ((redir->next->sign == 2 || redir->next->sign == 4) && redir->next->dest)
			redir = redir->next;
		fd = open(redir->dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (redir->sign == 3 || redir->sign == 5)
	{
		while ((redir->next->sign == 3 || redir->next->sign == 5) && redir->next->dest)
			redir = redir->next;
		fd = open(redir->dest, O_RDONLY);
	}
	return (fd);
}