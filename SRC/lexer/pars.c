/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:51:39 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/17 15:11:42 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"



void	lexer(char *line)
{
	char **division;
	t_lexer	lexer;
	
	division = cool_split(line, ' ');
}

void	tokenize(char **tokens, t_lexer *lexer)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	lexer = my_malloc(sizeof(t_lexer));
	while (tokens[i])
	{
		if (!check_sign)
		{
			lexer->content = my_malloc(sizeof(ft_strlen(tokens[i])));
			lexer->content = 

		
		{
			lexer->sign = my_malloc(sizeof(ft_strlen(tokens[i])));
			
		}
	}
}

int	check_sign(char	*s, t_lexer *lexer)
{
	if (!ft_strncmp(s, ">\0", 2) || !ft_strncmp(s, "<\0", 2) ||
	 !ft_strncmp(s, ">>\0", 3) || !ft_strncmp(s, "<<\0", 3) ||
	 !ft_strncmp(s, "|\0", 2))
		return(1);
	return(0);		
}
