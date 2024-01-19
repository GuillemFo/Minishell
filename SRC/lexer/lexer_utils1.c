/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:35:16 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/19 13:43:17 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	tokenize(t_lexer *lexer, char **split)
{
	int	i;

	i = 0;
	lexer = my_malloc(sizeof(t_lexer) * 2);
	while (split[i])
	{
		if (!is_sign(split[i][0]))
		{
			
		}
	}
}