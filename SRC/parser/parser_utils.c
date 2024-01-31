/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:40:26 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/31 14:26:23 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	cmd_count(t_lexer *lexer)
{
	int	i;
	
	i = 0;
	while (lexer && lexer->sign[0] != '|')
	{
		if (lexer->sign[0] !='N')
			i--;
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

t_sign	get_sign(char *sign)
{
	if (ft_strncmp(sign, "<\0", 2))
		return (3);
	if (ft_strncmp(sign, ">\0", 2))
		return (1);
	if (ft_strncmp(sign, "<<\0", 3))
		return (4);
	if (ft_strncmp(sign, ">>\0", 2))
		return (2);
}