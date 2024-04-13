/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:37:54 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 12:03:13 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	get_token(t_parser *parser, t_lexer *lexer, t_redir *tmp)
{
	parser->redir->next->dest = token(parser->redir->next->dest, lexer->content,
			ft_strlen(lexer->content));
	parser->redir = tmp;
}
