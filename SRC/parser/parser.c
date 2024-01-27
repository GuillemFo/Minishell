/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:13 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/27 19:06:56 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	parser(t_lexer *lexer)
{
	t_parser	*parser;
	
}

void	parsing_content(t_lexer *lexer, t_parser *parser)
{
	int	i;
	int	j;
	char	**words;

	i = 0;
	j = 0;
	while (lexer->content)
	{
		
	}
}

t_parser	*parser_creator()
{
	t_parser	*parser;
	
	parser = my_malloc(sizeof(t_lexer));
	parser->next = NULL;
	return(parser);
}
