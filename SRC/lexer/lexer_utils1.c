/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:35:16 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/27 19:07:27 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_lexer	*tokenize(t_lexer *lexer, char **split)
{
	int	i;
	t_lexer	*tmp;

	i = 0;
	lexer = lexer_creator();
	tmp = lexer;
	while (split[i])
	{
		if (!is_sign(split[i][0]))
		{
			lexer->content = split[i];
			lexer->sign = ft_strdup("NONE");
		}
		else if (is_sign(split[i][0]))
		{
			lexer->content = NULL;
			lexer->sign = split[i];
		}
		i++;
		if (!split[i])
			break ;
		lexer->next = lexer_creator();
		lexer = lexer->next;
	}
	return(tmp);
}

t_lexer	*lexer_creator()
{
	t_lexer	*lexer;
	
	lexer = my_malloc(sizeof(t_lexer));
	lexer->next = NULL;
	return(lexer);
}