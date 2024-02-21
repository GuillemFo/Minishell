/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/21 11:55:35 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//the idea is to check if quotes are paired. and after that, we can copy the before, content and after of each one.

bool	closed_quotes(char *str)
{
	int sq;
	int dq;
	int i;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			sq++;
			i++;
			while (str[i] != '\'' && str[i] != '\0')
			{
				i++;
			}
			if (str[i] == '\'')
				sq++;
		}
		else if (str[i] == '\"')
		{
			dq++;
			i++;
			while (str[i] != '\"' && str[i] != '\0')
				i++;
			if (str[i] == '\"')
				dq++;
		}
		i++;
	}
	if (sq % 2 == 0 && dq % 2 == 0)
		return (true);
	return (false);
}

//maybe iterate and check if it has quotes before trying to clean them??
void	clear_quotes(char *str)
{
	int		i;
	char	*bef_q;
	char	*cont_q;
	char	*after_q;

	i = 0;
	if (closed_quotes(str) == false)
		return (perror("Quotes not closed\n"));
	while (str[i] != '\0')
	{
		while ((str[i] != '\"' && str[i] != '\'') || str[i] != '\0')
			i++;
		if (str[i] == '\0')
		{
			
		}
		
	}
	
}