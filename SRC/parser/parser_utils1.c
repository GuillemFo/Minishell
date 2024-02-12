/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:21:15 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/11 17:18:46 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	**commands(t_lexer *lexer)
{
	char	**coms;

	
	coms = my_malloc(sizeof(char *) * (cmd_count(lexer) + 1));
	coms[cmd_count(lexer)] = NULL;
	return(coms);
}