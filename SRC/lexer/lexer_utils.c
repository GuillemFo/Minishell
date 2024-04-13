/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:50:34 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 12:01:48 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	free_matrix(char **matrix, size_t p)
{
	size_t	i;

	i = 0;
	while (i < p)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	*my_malloc(size_t bytes)
{
	void	*res;

	res = malloc(bytes);
	if (!res)
		exit(1);
	return (res);
}

int	is_quote(char letter)
{
	if (letter == 39)
		return (39);
	if (letter == 34)
		return (34);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	return (0);
}

int	is_sign(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (2);
	if (c == '<')
		return (3);
	else
		return (0);
}
