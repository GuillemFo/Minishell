/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:13 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/11 15:23:22 by adanylev         ###   ########.fr       */
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
			ft_printf("cmd: %s\n", parser->cmd[i]);
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

void	parsing_rest(t_lexer *lexer, t_parser *parser)
{
	t_redir	*tmp;
	
	if (!parser->redir)
		parser->redir = redir_creator();
	tmp = parser->redir;
	while (parser->redir && parser->redir->next)
		parser->redir = parser->redir->next;
	parser->redir->next = redir_creator();
	parser->redir->next->sign = lexer->sign;
	//ft_printf("sign: %d\n", parser->redir->sign);
	if (!lexer->next)
		error_parser("syntax error near unexpected token `newline'");
	lexer = lexer->next;
	if (lexer->sign != 0)
	 	error_parser("syntax error near unexpected token");
	parser->redir->next->dest = token(parser->redir->next->dest, lexer->content, ft_strlen(lexer->content));
	//ft_printf("dest: %s\n", parser->redir->dest);
	parser->redir = tmp;
}

void	parser_content(t_lexer *lexer, t_parser *parser)
{
	int	i;
	t_parser	*tmp;

	i = 0;
	parser->cmd = my_malloc(sizeof(char *) * (cmd_count(lexer) + 1));
	tmp = parser;
	parser->cmd[cmd_count(lexer)] = NULL;
	while (lexer)
	{
		if (lexer->sign == 1)
		{
			parser->next = parser_creator();
			parser = parser->next;
			i = 0;
			if (!lexer->next)
				error_parser("Error: unclosed pipe\n");
			parser->cmd = my_malloc(sizeof(char *) * (cmd_count(lexer->next) + 1));
			parser->cmd[cmd_count(lexer->next)] = NULL;
		}
		else if (lexer->sign != 0)
		{
			parsing_rest(lexer, parser);
			parser->redir = parser->redir->next;
			lexer = lexer->next;
		}
		else if (lexer && lexer->content)
		{
			parser->cmd[i] = token(parser->cmd[i], lexer->content, ft_strlen(lexer->content) + 1);
			//ft_printf("cmd: %s\n", parser->cmd[i]);
			i++;
		}
		lexer = lexer->next;
	}
	// i = 0;
	// while(tmp)
	// {
	// 	i = 0;
	// 	while(tmp->cmd[i])
	// 	{
	// 		printf("%s\n", tmp->cmd[i]);
	// 		i++;
	// 	}
	// 	tmp = tmp->next;
	// }
}


t_parser	*parser_creator()
{
	t_parser	*parser;
	
	parser = my_malloc(sizeof(t_parser));
	parser->next = NULL;
	parser->redir = NULL;
	return(parser);
}
