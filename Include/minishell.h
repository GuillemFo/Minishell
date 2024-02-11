/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:20:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/11 17:20:29 by adanylev         ###   ########.fr       */
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


typedef	enum
{
	PIPE = 1,
	GREATER = 2,
	LESS = 3,
	GREATER2 = 4,
	LESSLESS = 5
}		t_sign;

typedef	struct s_lexer
{
	char					*content;
	t_sign					sign;
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
void	ft_lexer(char *line);
char	**new_split(char *line, int wc, int i, int k);
void	sign_situation(char *line, char	**split, int *j, int *i);
char 	*ft_substri(const char *str, int start, int len);
void	get_word(int k, int *i, char *line, char **split);
char 	*ft_strncpy(char *s1, char *s2, int n);
char	*token(char *dest, char *src, int len);
void	sign(t_lexer *lexer, char *split);
t_lexer	*tokenize(t_lexer *lexer, char **split);
t_lexer	*lexer_creator();

/*-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-=-=-=-PARSER-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

typedef	struct	s_redir
{
	t_sign			sign;
	char			*dest;
	struct s_redir	*next;
}				t_redir;

typedef	struct s_parser
{
	char			**cmd;
	t_redir			*redir;
	struct s_parser	*next;
}				t_parser;

int			cmd_count(t_lexer *lexer);
char		**parser_split(t_lexer *lexer, t_parser *parser);
void		ft_parser(t_lexer *lexer);
t_sign		get_sign(char *sign);
t_parser	*parser_creator();
void 		error_parser(char *msg);
void		parser_content(t_lexer *lexer, t_parser *parser, int i);
void		parsing_rest(t_lexer *lexer, t_parser *parser);
t_redir		*redir_creator();
void		first_redir(t_lexer	*lexer, t_parser *parser);
char		**commands(t_lexer *lexer);

#endif