/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:21:15 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/12 11:37:07 by adanylev         ###   ########.fr       */
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

void	break_free(t_lexer	*lexer)
{
	while (lexer != NULL)
	{
		if (lexer->content)
			free(lexer->content);
		free(lexer);
		lexer = lexer->next;
	}
}