/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:21:15 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/22 15:05:57 by adanylev         ###   ########.fr       */
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

void	free_parser(t_parser *parser)
{
	t_parser *tmp;
	t_redir	*temp;

	tmp = parser;
	while (parser != NULL)
	{
		parser = parser->next;
		if (tmp->cmd)
			free_matrix(tmp->cmd, matrix_size(tmp->cmd));
		while (tmp->redir)
		{
			temp = tmp->redir;
			tmp->redir = tmp->redir->next;
			if (tmp->redir)
				free(tmp->redir);
			tmp->redir = temp;
		}
		free(tmp);
		tmp = parser;
	}
}

int	matrix_size(char **pars_cmds)
{
	int	i;
	
	i = 0;
	while(pars_cmds[i])
		i++;
	return (i);
}