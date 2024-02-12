/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:21:15 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/12 12:50:48 by adanylev         ###   ########.fr       */
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
	t_lexer *tmp;

	tmp = lexer;
	while (lexer != NULL)
	{
		lexer = lexer->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = lexer;
	}
}