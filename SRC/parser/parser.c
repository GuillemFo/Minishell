/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:13 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/31 15:14:02 by adanylev         ###   ########.fr       */
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

	
}

void	parsing_rest(t_lexer *lexer, t_parser *parser)
{
	int	i;

	i = 0;
	parser->redir.sign = get_sign(lexer->sign);
	if (lexer->next)
	{
		lexer = lexer->next;
		if (lexer->sign[0] != 'N')
					
}

void	parser_content(t_lexer *lexer, t_parser *parser)
{
	int	i;

	i = 0;
	parser->cmd = my_malloc(sizeof(char *) * (cmd_count(lexer) + 1));
	while (lexer && lexer->sign[0] != '|')
	{
		if (lexer->content)
			parser->cmd[i] = token(parser->cmd[i], lexer->content, ft_strlen(lexer->content) + 1);
		else
			parsing_rest(lexer, parser);
		lexer = lexer->next;
		i++;
		
	}
	parser->cmd[i] = NULL;
}


// t_parser	*parser_creator()
// {
// 	t_parser	*parser;
	
// 	parser = my_malloc(sizeof(t_parser));
// 	parser->next = NULL;
// 	return(parser);
// }