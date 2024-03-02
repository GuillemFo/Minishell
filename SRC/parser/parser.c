/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:13 by adanylev          #+#    #+#             */
/*   Updated: 2024/03/02 18:39:58 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_parser	*ft_parser(t_lexer *lexer, int *error)
{
	t_parser	*parser;
	t_parser	*tmp;
	int	i;

	i = 0;
	parser = NULL;
	parser = parser_creator();
	tmp = parser;
	parser_content(lexer, parser, i, error);
	break_free(lexer);
	// while (parser)
	// {
	// 	i = 0;
	// 	while(parser->cmd[i])
	// 	{
	// 		ft_printf("cmd: %s\n", parser->cmd[i]);
	// 		i++;
	// 	}
	// 	while (parser->redir)
	// 	{
	// 		ft_printf("sign: %d\n", parser->redir->sign);
	// 		ft_printf("dest: %s\n", parser->redir->dest);
	// 		parser->redir = parser->redir->next;
	// 	}
	// 	parser = parser->next;
	// }
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
		{
			parser->redir->next->dest = token(parser->redir->next->dest, lexer->content, ft_strlen(lexer->content));
			parser->redir = tmp;
		}
	}
}

void	first_redir(t_lexer	*lexer, t_parser *parser, int *error)
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
			parser->redir->dest = token(parser->redir->dest, lexer->content, ft_strlen(lexer->content));
	}
}

void	parser_content(t_lexer *lexer, t_parser *parser, int i, int *error)
{
	parser->cmd = commands(lexer);
	while (lexer)
	{
		if (lexer->sign == 1)
		{
			if (!lexer->next)
				ft_other_error("Error: unclosed pipe\n", error, 1);
			else
			{
				parser->next = parser_creator();
				parser = parser->next;
				i = 0;
				parser->cmd = commands(lexer->next);
			}
		}
		else if (lexer->sign != 0)
		{
			parsing_rest(lexer, parser, error);
			if (lexer->next)
				lexer = lexer->next;
		}
		else if (lexer && lexer->content)
		{
			parser->cmd[i] = token(parser->cmd[i], lexer->content, ft_strlen(lexer->content) + 1);
			i++;
		}
		//if (lexer && lexer->next)
		lexer = lexer->next;
	}
}


t_parser	*parser_creator()
{
	t_parser	*parser;
	
	parser = my_malloc(sizeof(t_parser));
	parser->next = NULL;
	parser->redir = NULL;
	return(parser);
}
