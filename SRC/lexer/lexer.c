/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:50 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 12:01:29 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_lexer	*ft_lexer(char *line)
{
	t_lexer	*lexer;
	int		i;
	int		wc;
	char	**c;

	lexer = NULL;
	i = 0;
	wc = 0;
	if (ft_strcmp(line, "\"\"") == 0)
		return (NULL);
	if (ft_strcmp(line, "\'\'") == 0)
		return (NULL);
	while (line[i] && (line[i] == '\t' || line[i] == '\n' || line[i] == 32))
		i++;
	if (line[i] == '\0')
		return (NULL);
	i = 0;
	c = new_split(line, arg_count(line, i, wc), i, wc);
	lexer = tokenize(lexer, c);
	return (lexer);
}

int	arg_count(char *line, int i, int wc)
{
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_sign(line[i]))
		{
			if (line[i + 1] && is_redir(line[i])
				&& is_redir(line[i]) == is_redir(line[i + 1]))
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
			while (line[i] && !is_space(line[i]) && !is_sign(line[i]))
				i++;
			wc++;
		}
	}
	return (wc);
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

void	sign_situation(char *line, char **split, int *j, int *i)
{
	if (line + 1 && is_redir(*line) && is_redir(*line) == is_redir(*(line + 1)))
	{
		split[++(*j)] = my_malloc(sizeof(char) * 2 + 1);
		ft_strncpy(split[(*j)], line, 2);
		(*i)++;
	}
	else
	{
		split[++(*j)] = my_malloc(sizeof(char) * 1 + 1);
		ft_strncpy(split[(*j)], line, 1);
	}
	(*i)++;
}
