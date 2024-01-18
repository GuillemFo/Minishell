/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:20:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/18 13:19:38 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <./readline/history.h>
# include <./readline/readline.h>
# include "stdlib.h"
# include "stdio.h"

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-LEXER-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

typedef	struct s_lexer
{
	char			*content;
	char			*sign;
	struct t_lexer	*next;
}				t_lexer;

char	**free_matrix(char **matrix, size_t p);
void	*my_malloc(size_t bytes);
int		is_quote(char letter);
int		is_space(char c);
int		is_sign(char c);
int		quote_situation(char *c);
int		arg_count(char *line, int i, int wc);
void	lexer(char *line);


#endif