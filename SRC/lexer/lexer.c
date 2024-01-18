/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:50 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/18 13:19:29 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	lexer(char *line)
{
	t_lexer	lexer;
	int	i;
	int	wc;
	int	count;

	i = 0;
	wc = 0;
	count = arg_count(line, i, wc);
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

/*char **cool_split(char *str, char c)
{
	int	i;
	int	start;
	int	k;
	char **split;
	int	quotes;

	i = 0;
	quotes = 0;
	start = 0;
	k = 0;
	split = my_malloc(sizeof(char *) * (count_words(str) + 1));
	if (!split)
		return (NULL);
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			c = is_quote(str[i]);
			quotes++;
		}
		if (i == 0 && !is_space(str[i]))
			start = i;
		else if (i > 0 && !is_space(str[i]) && is_space(str[i - 1]))
			start = i;
		if(!is_space(str[i]) && (is_space(str[i + 1]) || str[i + 1] == '\0'))
		{
			split[k++] = ft_substri(str, start, i - start + 1);
		}
		if (quotes % 2 == 0)
			c = ' ';
		i++;
	}
	split[k] = NULL;
	return (split);
}*/
