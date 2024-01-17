/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:50:34 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/17 14:45:11 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**free_matrix(char **matrix, size_t p)
{
	size_t	i;

	i = 0;
	while (i < p)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

void	*my_malloc(size_t bytes)
{
	void	*res;

	res = malloc(bytes);
	if (!res)
		exit(1);
	return (res);
}