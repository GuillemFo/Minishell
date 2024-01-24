/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:21:33 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/24 11:48:17 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char *ft_strncpy(char *s1, char *s2, int n)
{
	int i = -1;

	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

char	**new_split(char *line, int wc, int i, int k)
{
	char	**split;
	int	j;
	
	j = -1;
	split = my_malloc(sizeof(char *) * (wc + 2));
	while(line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_sign(line[i]))
			sign_situation(&line[i], split, &j, &i);
		else if (quote_situation(&line[i]))
		{
			split[++j] = my_malloc(sizeof(char) * quote_situation(&line[i]) + 1);
			ft_strncpy(split[j], &line[i], (int)quote_situation(&line[i]) + 1);
			i = i + quote_situation(&line[i]) + 1;
		}
		else
			get_word(k, &i, line, &split[++j]);
	}
	split[++j] = NULL;
	return (split);
}

void	sign_situation(char *line, char	**split, int *j, int *i)
{
	if (line + 1 && is_sign(*line) == is_sign(*line + 1))
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

void	get_word(int k, int *i, char *line, char **split)
{
	k = *i;
	while (line[*i] && !is_quote(line[*i]) && !is_space(line[*i]) && !is_sign(line[*i]))
		(*i)++;
	if (*i > k)
	{
		*split = my_malloc(sizeof(char) * (*i - k) + 1);
		ft_strncpy(*split, &line[k], *i - k);
	}
}