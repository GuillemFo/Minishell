/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:13 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/29 15:10:56 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

// int	main()
// {
// 	char	line[] = " echo 'ls''|''cat' |grep -v";
// 	ft_lexer(line);
// 	return (0);
// }

void	ft_parser(t_lexer *lexer)
{
	t_parser	*parser;
	int	i;

	parser = NULL;
	i = 0;
	parser->cmd = parser_content(lexer, parser);
	
}


void	parsing_rest(t_lexer *lexer, t_parser *parser)
{
	int	i;

	i = 0;
	while (lexer)
	{
		
	}
	
}

char	**parser_content(t_lexer *lexer, t_parser *parser)
{
	(void)parser;
	int	i;
	t_lexer *tmp;
	
	tmp = lexer;
	i = 0;
	char **cmds;
	cmds = my_malloc(sizeof(char *) * (cmd_count(lexer) + 1));
	while (lexer && lexer->sign[0] != '|')
	{
		if (lexer->content)
			cmds[i] = token(cmds[i], lexer->content, ft_strlen(lexer->content) + 1);
		lexer = lexer->next;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

// t_parser	*parser_creator()
// {
// 	t_parser	*parser;
	
// 	parser = my_malloc(sizeof(t_lexer));
// 	parser->next = NULL;
// 	return(parser);
// }
