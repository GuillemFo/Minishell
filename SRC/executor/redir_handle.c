/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:34:29 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 14:35:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	redir_manager(t_parser *parser)
{
	int		f;
	t_redir	*aux;

	aux = parser->redir;
	while (aux)
	{
		if (aux->sign == 2 || aux->sign == 4)
		{
			f = find_last_redir_out(aux);
			if (f < 0)
				error_child(1, aux->dest, 1);
			dup2(f, STDOUT_FILENO);
		}
		if (aux->sign == 3 || aux->sign == 5)
		{
			f = find_last_redir_in(aux);
			if (f < 0)
				error_child(1, aux->dest, 1);
			dup2(f, STDIN_FILENO);
		}
		close(f);
		if (aux->sign == LESSLESS)
			unlink(aux->dest);
		aux = aux->next;
	}
}

int	find_last_redir_out(t_redir *redir)
{
	int	fd;

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

int	find_last_redir_in(t_redir *redir)
{
	int	fd;

	fd = -1;
	while (redir != NULL)
	{
		if ((redir->sign == 3 || redir->sign == 5) && redir->dest != NULL)
		{
			if (access(redir->dest, F_OK) == -1)
				error_child(3, redir->dest, 1);
			fd = open(redir->dest, O_RDONLY);
			if (fd == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (fd);
}
