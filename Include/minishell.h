/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:20:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/17 14:59:37 by adanylev         ###   ########.fr       */
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
	struct t_lexer *next;
}				t_lexer;


//cuando voy a ejecutar neceisto convertir content en un argv
execve(argv[0], argv, env);
/*
"hola que tal como estas | muy bien"
argv[0] = "hola"
argv[1] = "que"
argv[2] = "tal"
argv[3] = "como"
argv[4] = "estas"
*/

char	**cool_split(char *str, char c);
char	**free_matrix(char **matrix, size_t p);
void	*my_malloc(size_t bytes);

#endif