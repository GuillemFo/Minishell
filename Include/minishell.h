/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:20:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/26 20:08:30 by adanylev         ###   ########.fr       */
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
	struct s_lexer			*next;
}					t_lexer;

void	lexer(char *line);
char	**free_matrix(char **matrix, size_t p);
void	*my_malloc(size_t bytes);
int		is_quote(char letter);
int		is_space(char c);
int		is_sign(char c);
int		quote_situation(char *c);
int		arg_count(char *line, int i, int wc);
void	lexer(char *line);
char	**new_split(char *line, int wc, int i, int k);
void	sign_situation(char *line, char	**split, int *j, int *i);
char 	*ft_substri(const char *str, int start, int len);
void	get_word(int k, int *i, char *line, char **split);
t_lexer	*tokenize(t_lexer *lexer, char **split);
t_lexer	*lexer_creator();


/*-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-=-=-=-PARSER-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


#endif