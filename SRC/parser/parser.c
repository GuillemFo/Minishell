/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:13 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/06 16:07:09 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_parser	*ft_parser(t_lexer *lexer, int *error)
{
	t_parser	*parser;
	int			i;

	i = 0;
	parser = NULL;
	if (!lexer)
		return (NULL);
	parser = parser_creator();
	if (lexer->sign == PIPE)
	{
		ft_other_error("Error: pipe not used correctly\n", error, 1);
		free(parser);
		break_free(lexer);
		return (NULL);
	}
	parser_content(lexer, parser, i, error);
	break_free(lexer);
	return (parser);
}

void	parsing_rest(t_lexer *lexer, t_parser *parser, int *error)
{
	t_redir	*tmp;

	if (!parser->redir)
	{
		first_redir(lexer, parser, error);
		return ;
	}
	tmp = parser->redir;
	while (parser->redir && parser->redir->next)
		parser->redir = parser->redir->next;
	parser->redir->next = redir_creator();
	parser->redir->next->sign = lexer->sign;
	if (!lexer->next)
		ft_other_error("syntax error near unexpected token\n", error, 2);
	else
	{
		lexer = lexer->next;
		if (lexer->sign != 0)
			ft_other_error("syntax error near unexpected token\n", error, 2);
		else
			get_token(parser, lexer, tmp);
	}
}

void	first_redir(t_lexer *lexer, t_parser *parser, int *error)
{
	parser->redir = redir_creator();
	parser->redir->sign = lexer->sign;
	if (!lexer->next)
		ft_other_error("syntax error near unexpected token\n", error, 2);
	else
	{
		lexer = lexer->next;
		if (lexer->sign != 0)
			ft_other_error("syntax error near unexpected token\n", error, 2);
		else
			parser->redir->dest = token(parser->redir->dest, lexer->content,
					ft_strlen(lexer->content));
	}
}

void	parser_content(t_lexer *lexer, t_parser *parser, int i, int *error)
{
	parser->cmd = commands(lexer);
	while (lexer)
	{
		if (lexer->sign == PIPE)
		{
			if (!lexer->next || lexer->next->sign == PIPE)
				ft_other_error("Error: pipe not used correctly\n", error, 1);
			else
				parser = parser_update(parser, &i, lexer);
		}
		else if (lexer->sign != 0)
		{
			parsing_rest(lexer, parser, error);
			if (lexer->next && lexer->next->sign != PIPE)
				lexer = lexer->next;
		}
		else if (lexer && lexer->content && ++i)
			parser->cmd[i - 1] = token(parser->cmd[i - 1], lexer->content,
					ft_strlen(lexer->content) + 1);
		if (*error)
			return ;
		lexer = lexer->next;
	}
}

t_parser	*parser_creator(void)
{
	t_parser	*parser;

	parser = my_malloc(sizeof(t_parser));
	parser->next = NULL;
	parser->redir = NULL;
	parser->cmd = NULL;
	return (parser);
}
