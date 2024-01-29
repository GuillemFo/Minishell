/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:40:26 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/29 12:55:46 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	cmd_count(t_lexer *lexer)
{
	int	i;
	
	i = 0;
	while (lexer && lexer->sign[0] != '|')
	{
		lexer = lexer->next;
		i++;
	}
	return (i);
}

int	big_count(t_lexer *lexer)
{
	int	i;
	
	i = 0;
	while (lexer)
	{
		if (lexer->sign[0] == '|')
			i++;
		lexer = lexer->next;
	}
	return (i);
}