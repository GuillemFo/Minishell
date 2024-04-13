/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:21:15 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 12:03:00 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	**commands(t_lexer *lexer)
{
	char	**coms;

	if (cmd_count(lexer) == 0)
		return (NULL);
	coms = my_malloc(sizeof(char *) * (cmd_count(lexer) + 1));
	coms[cmd_count(lexer)] = NULL;
	return (coms);
}

void	break_free(t_lexer *lexer)
{
	t_lexer	*tmp;

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

void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (redir != NULL)
	{
		redir = redir->next;
		if (temp->dest)
			free(temp->dest);
		free(temp);
		temp = redir;
	}
}

void	free_parser(t_parser *parser)
{
	t_parser	*tmp;

	tmp = parser;
	while (parser)
	{
		if (tmp->cmd)
			free_matrix(tmp->cmd, matrix_size(tmp->cmd));
		if (tmp->redir)
			free_redir(tmp->redir);
		parser = parser->next;
		free(tmp);
		tmp = parser;
	}
}

int	matrix_size(char **pars_cmds)
{
	int	i;

	i = 0;
	if (pars_cmds[i])
	{
		while (pars_cmds[i])
			i++;
	}
	return (i);
}
