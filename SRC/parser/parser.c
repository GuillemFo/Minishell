/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:13 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/12 14:04:17 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	main()
{
	t_lexer	*lexer;
	t_parser	*parser;
	int	i;
	
	char	line[] = "echo >> kk";
	lexer = ft_lexer(line);
	parser = ft_parser(lexer);
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
	// 	printf("next: \n");
	// 	parser = parser->next;
	// }
	break_free(lexer);
	return (0);
}

t_parser	*ft_parser(t_lexer *lexer)
{
	t_parser	*parser;
	t_parser	*tmp;
	int	i;

	i = 0;
	parser = NULL;
	parser = parser_creator();
	tmp = parser;
	parser_content(lexer, parser, i);
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

void	parsing_rest(t_lexer *lexer, t_parser *parser)
{
	t_redir	*tmp;
	
	if (!parser->redir)
	{
		first_redir(lexer, parser);
		return ;
	}
	tmp = parser->redir;
	while (parser->redir && parser->redir->next)
		parser->redir = parser->redir->next;
	parser->redir->next = redir_creator();
	parser->redir->next->sign = lexer->sign;
	if (!lexer->next)
		error_parser("syntax error near unexpected token `newline'");
	lexer = lexer->next;
	if (lexer->sign != 0)
	 	error_parser("syntax error near unexpected token");
	parser->redir->next->dest = token(parser->redir->next->dest, lexer->content, ft_strlen(lexer->content));
	parser->redir = tmp;
}

void	first_redir(t_lexer	*lexer, t_parser *parser)
{
	parser->redir = redir_creator();
	parser->redir->sign = lexer->sign;
	if (!lexer->next)
		error_parser("syntax error near unexpected token `newline'");
	lexer = lexer->next;
	if (lexer->sign != 0)
	 	error_parser("syntax error near unexpected token");
	parser->redir->dest = token(parser->redir->dest, lexer->content, ft_strlen(lexer->content));
}

void	parser_content(t_lexer *lexer, t_parser *parser, int i)
{
	parser->cmd = commands(lexer);
	while (lexer)
	{
		if (lexer->sign == 1)
		{
			parser->next = parser_creator();
			parser = parser->next;
			i = 0;
			if (!lexer->next)
				error_parser("Error: unclosed pipe\n");
			parser->cmd = commands(lexer->next);
		}
		else if (lexer->sign != 0)
		{
			parsing_rest(lexer, parser);
			lexer = lexer->next;
		}
		else if (lexer && lexer->content)
		{
			parser->cmd[i] = token(parser->cmd[i], lexer->content, ft_strlen(lexer->content) + 1);
			i++;
		}
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
