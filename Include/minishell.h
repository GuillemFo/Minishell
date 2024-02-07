/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:20:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/07 11:18:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <sys/param.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdbool.h>
# include <history.h>
# include <readline.h>

/*-=-=-=-=-=-=-=-=STRUCTS=-=-=-=-=-=-=-=-*/

typedef	struct s_env
{
	char			*name;
	char			*content;
	bool			is_hidden;
	struct s_env	*next;
}					t_env;


void	handle_sigint(int sig);
void	handle_sigquit(int sig);

// NEEDS TO BE READAPTED TO ANNA'S CODE
// so all info gonna be stored at parser->cmd[i] and next node when encountering pipes or redirections and so.
//	/*-=-=-=-=-=-=-=-=-=-=-=BUILTINS=-=-=-=-=-=-=-=-=-=-=-=*/
//	
//	int	is_builtin(t_parser *token, t_env *env);
//	int	built_ls();
//	int	built_grep();
//	t_env	*load_env(char **envp);
//	int		print_env_lst(t_env *env);
//	bool		env_exist(t_env *env, t_parser *token);
//	char	*env_exist_2(t_env *env, char *name);
//	t_env	*del_env(t_parser *token, t_env *env);
//	t_env	*add_env(t_parser *token, t_env *env);
//	
//	/*-=-=-=-=-=-=-=-=EXPANSOR=-=-=-=-=-=-=-=-=-=-=*/
//	char	*find_dollar(char *str, t_env *env);
//	
//	/*-=-=-=-=-=-=-=-=-=-=-=TOOLS=-=-=-=-=-=-=-=-=-=-=*/
//	int	errno_printer(char *com, char *error_txt, char *asked);
//	char *trim_after(char *str, char c);
//	char *trim_bef(char *str, char c);


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-ANNA-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-LEXER-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

typedef	struct s_lexer
{
	char					*content;
	char					*sign;
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
t_lexer	*tokenize(t_lexer *lexer, char **split);
t_lexer	*lexer_creator();

/*-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-=-=-=-PARSER-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

typedef	enum
{
	GREATER = 1,
	GREATER2 = 2,
	LESS = 3,
	LESSLESS = 4
}		t_sign;

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
void		parser_content(t_lexer *lexer, t_parser *parser);


#endif