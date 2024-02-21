/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:34:29 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/21 15:19:33 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	redir_type(t_parser *parser)
{
	if (parser->redir->sign == 2)
		redir_out()
}

void	redir_out(t_parser *parser)
{
	
}

int	find_last_redir(t_redir *redir)
{
	int	fd;
	while(redir)
	{
		if()
	}
}