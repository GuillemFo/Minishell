/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:35:16 by adanylev          #+#    #+#             */
/*   Updated: 2024/04/13 12:02:21 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_lexer	*tokenize(t_lexer *lexer, char **split)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	lexer = lexer_creator();
	tmp = lexer;
	while (split[i])
	{
		if (!is_sign(split[i][0]))
		{
			lexer->content = token(lexer->content, split[i], ft_strlen(split[i])
					+ 1);
			lexer->sign = 0;
		}
		else if (is_sign(split[i][0]))
			sign(lexer, &split[i][0]);
		i++;
		if (!split[i])
			break ;
		lexer->next = lexer_creator();
		lexer = lexer->next;
	}
	free_matrix(split, i);
	return (tmp);
}

void	sign(t_lexer *lexer, char *split)
{
	lexer->content = NULL;
	if (split[1] && is_redir(split[0])
		&& is_redir(split[0]) == is_redir(split[1]))
	{
		if (is_sign(split[0]) == 2)
			lexer->sign = GREATER2;
		else if (is_sign(split[0]) == 3)
			lexer->sign = LESSLESS;
	}
	else
		lexer->sign = is_sign(split[0]);
}

char	*token(char *dest, char *src, int len)
{
	dest = my_malloc(sizeof(char) * (len + 1));
	dest = ft_strncpy(dest, src, len);
	return (dest);
}

t_lexer	*lexer_creator(void)
{
	t_lexer	*lexer;

	lexer = my_malloc(sizeof(t_lexer));
	lexer->content = NULL;
	lexer->sign = 0;
	lexer->next = NULL;
	return (lexer);
}

int	is_redir(char c)
{
	if (c == '>')
		return (2);
	if (c == '<')
		return (3);
	else
		return (0);
}
