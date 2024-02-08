/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:13 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/08 15:12:10 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	main()
{
	char	line[] = " echo 'ls' > out > ik|'cat' grep -v | ls cat |kk << p";
	ft_lexer(line);
	
	return (0);
}

void	ft_parser(t_lexer *lexer)
{
	t_parser	*parser;
	t_parser	*tmp;
	int	i;

	i = 0;
	parser = NULL;
	parser = parser_creator();
	tmp = parser;
	parser_content(lexer, parser);
	i = 0;
	while (parser)
	{
		i = 0;
		while(parser->cmd[i])
		{
			ft_printf("cmd: %s\n", tmp->cmd[i]);
			i++;
		}
		while (parser->redir)
		{
			ft_printf("sign: %d\n", parser->redir->sign);
			ft_printf("dest: %s\n", parser->redir->dest);
			parser->redir = parser->redir->next;
		}
		parser = parser->next;
	}
 }

int	parsing_rest(t_lexer *lexer, t_parser *parser)
{
	int	i;

	parser->redir = redir_creator();
	i = 0;
	parser->redir->sign = get_sign(lexer->sign);
	ft_printf("sign: %d\n", parser->redir->sign);
	if (lexer->next)
	{
		lexer = lexer->next;
		// if (lexer->sign[0] != 'N')
		// 	error_parser("syntax error near unexpected token");
		parser->redir->dest = token(parser->redir->dest, lexer->content, ft_strlen(lexer->content));
	//	ft_printf("dest: %s\n", parser->redir->dest);
		return (1);
	}
	return (0);
}

void	parser_content(t_lexer *lexer, t_parser *parser)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	parser->cmd = my_malloc(sizeof(char *) * (cmd_count(lexer) + 1));
	parser->cmd[cmd_count(lexer)] = NULL;
	while (lexer)
	{
		if (lexer->sign[0] == '|')
		{
			parser->next = parser_creator();
			parser = parser->next;
			i = 0;
			if (lexer->next)
			{
				parser->cmd = my_malloc(sizeof(char *) * (cmd_count(lexer->next) + 1));
				parser->cmd[cmd_count(lexer->next)] = NULL;
			}
		}
		else if (lexer->sign[0] != 'N')
		{
			if (parsing_rest(lexer, parser) == 1)
				lexer = lexer->next;			
		}
		else if (lexer && lexer->content)
		{
			parser->cmd[i] = token(parser->cmd[i], lexer->content, ft_strlen(lexer->content) + 1);
		//	ft_printf("cmd: %s\n", parser->cmd[i]);
			i++;
		}
		lexer = lexer->next;
	}
}


t_parser	*parser_creator()
{
	t_parser	*parser;
	
	parser = my_malloc(sizeof(t_parser) + 1);
	parser->next = NULL;
	return(parser);
}
