/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:40:26 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/04 11:52:43 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	cmd_count(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer && lexer->sign != 1)
	{
		if (lexer->sign != 0 && lexer->next && lexer->next->sign == 0)
			lexer = lexer->next;
		else if (lexer->sign == 0)
			i++;
		lexer = lexer->next;
	}
	return (i);
}

int	big_count(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		if (lexer->sign == 1)
			i++;
		lexer = lexer->next;
	}
	return (i);
}

t_sign	get_sign(char *sign)
{
	if (ft_strncmp(sign, "<\0", 2))
		return (LESS);
	if (ft_strncmp(sign, ">\0", 2))
		return (GREATER);
	if (ft_strncmp(sign, "<<\0", 3))
		return (LESSLESS);
	if (ft_strncmp(sign, ">>\0", 3))
		return (GREATER2);
	return (0);
}

t_redir	*redir_creator(void)
{
	t_redir	*redir;

	redir = my_malloc(sizeof(t_redir));
	redir->sign = 0;
	redir->dest = NULL;
	redir->next = NULL;
	return (redir);
}

t_parser	*parser_update(t_parser *parser, int *i, t_lexer *lexer)
{
	parser->next = parser_creator();
	parser = parser->next;
	*i = 0;
	parser->cmd = commands(lexer->next);
	return (parser);
}
