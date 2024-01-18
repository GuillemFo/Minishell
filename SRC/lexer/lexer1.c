/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:21:33 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/18 15:20:37 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	**new_split(char *line, int wc)
{
	char	**split;
	int	i;
	int	j;

	i = 0;
	j = 0;
	split = my_malloc(sizeof(char *) * (wc + 1));
	while(line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_sign(line[i]))
		{
			if (line[i + 1] && is_sign(line[i]) == is_sign(line[i + 1]))
			{
				split[j] = my_malloc(sizeof(char) * 2 + 1);
				ft_strncpy(split[j++], &line[i], 2);
				i++;
			}
			else
			{
				split[j] = my_malloc(sizeof(char) * 1 + 1);
				ft_strncpy(split[j++], &line[i], 1);
			}
			i++;
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