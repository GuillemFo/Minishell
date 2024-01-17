/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:50 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/17 14:46:47 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	is_quote(char letter)
{
	if (letter == 39)
		return (39);
	if(letter == 34)
		return (34);
	return (0);
}

int is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	return (0);
}
int count_words(char *str)
{
	int	i;
	int	wc;
	int	b;

	i = 0;
	b = 0;
	wc = 0;
	while (str[i])
	{
		if (i == 0 && !is_space(str[i]))
			wc++;
		if (i > 0 && !is_space(str[i]) && is_space(str[i - 1]))
			wc++;
		i++;
	}
	return (wc);
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

char **cool_split(char *str, char c)
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
}
