/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:21:33 by adanylev          #+#    #+#             */
/*   Updated: 2024/03/09 17:27:00 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

char	**new_split(char *line, int wc, int i, int k)
{
	char	**split;
	int		j;

	j = -1;
	split = my_malloc(sizeof(char *) * (wc + 1));
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_sign(line[i]))
			sign_situation(&line[i], split, &j, &i);
		else
			get_word(k, &i, line, &split[++j]);
	}
	split[++j] = NULL;
	return (split);
}

void	get_word(int k, int *i, char *line, char **split)
{
	k = *i;
	while (line[*i] && !is_space(line[*i]) && !is_sign(line[*i]))
	{
		if (quote_situation(&line[*i]))
		{
			*i += quote_situation(&line[*i]);
			if (line[*i + 1])
				*i = *i + 1;
		}
		else
			*i = *i + 1;
	}
	if (*i > k)
	{
		*split = my_malloc(sizeof(char) * (*i - k) + 1);
		ft_strncpy(*split, &line[k], *i - k);
	}
}
