/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:50 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/26 20:18:22 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	lexer(char *line)
{
	t_lexer	*lexer;
	int	i;
	int	wc;
	char	**c;

	
	lexer = NULL;
	i = 0;
	wc = 0;
	c = new_split(line, arg_count(line, i, wc), i, wc);
	lexer = tokenize(lexer, c);
	while (lexer)
	{
		printf("content: %s\n", lexer->content);
		printf("sign: %s\n", lexer->sign);
		lexer = lexer->next;
	}
}

int	arg_count(char *line, int i, int wc)
{
	while(line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_sign(line[i]))
		{
			if (line[i + 1] && is_sign(line[i]) == is_sign(line[i + 1]))
				i++;
			i++;
			wc++;
		}
		else if (quote_situation(&line[i]))
			i = i + quote_situation(&line[i]) + 1;
		else
		{
			while (line[i] && !is_space(line[i]) && !is_sign(line[i]))
				i++;
			wc++;
		}
	}
	return(wc);
}

int	quote_situation(char *c)
{
	int	i;
	int	j;

	i = 0;
	if (is_quote(c[i]) && c[i + 1])
	{
		j = i + 1;
		while (c[j] && c[i] != c[j])
			j++;
		if (is_quote(c[j]) == is_quote(c[i]))
			return (j);
		return (0);
	}
	return (0);
}