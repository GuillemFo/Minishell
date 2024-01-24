/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:50 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/24 12:22:55 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	main()
{
	t_lexer	*lexer;
	int	i;
	int	wc;
	char	**c;
	char	line[]= "lol p| grep -v >helo'bye'";

	
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
	return (0);
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
		{
			i = i + quote_situation(&line[i]) + 1;
			wc++;
		}
		else
		{
			while (line[i] && !is_quote(line[i]) && !is_space(line[i]) && !is_sign(line[i]))
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


char *ft_substri(const char *str, int start, int len)
{
	char *palabro;
	int i;

	i = 0;
	palabro = my_malloc(sizeof(char) * (len + 1));
	while(i < len)
	{
		palabro[i] = str[i + start];
		i++;
	}
	palabro[i] = '\0';
	return (palabro);
}