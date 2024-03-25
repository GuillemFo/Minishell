/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/03/26 00:48:51 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

/*-=-=-=-=-=-=-=-=LIBRARIES=-=-=-=-=-=-=-=-*/

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <history.h>
# include <readline.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

/*-=-=-=-=-=-=-=-=COLOR CODES=-=-=-=-=-=-=-=-*/

# define C_R "\x1b[31m" // RED
# define C_G "\x1b[32m" // GREEN
# define C_B "\x1b[34m" // BLUE
# define C_Y "\x1b[33m" // YELLOW
# define C_M "\x1b[35m" // MAGENTA
# define C_C "\x1b[36m" // CYAN
# define C_RESET "\x1b[0m"

/*-=-=-=-=-=-=-=-=STRUCTS=-=-=-=-=-=-=-=-*/

typedef enum
{
	PIPE = 1,
	GREATER,
	LESS,
	GREATER2, 
	LESSLESS,
}					t_sign;

typedef struct s_env
{
	char			*name;
	char			*content;
	bool			is_hidden;
	struct s_env	*next;
}					t_env;

typedef struct s_lexer
{
	char			*content;
	t_sign			sign;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_redir
{
	t_sign			sign;
	char			*dest;
	int				fd[2];
	struct s_redir	*next;
}					t_redir;

typedef struct s_parser
{
	char			**cmd;
	t_redir			*redir;
	struct s_parser	*next;
}					t_parser;

/*-=-=-=-=-=-=-=-=-=-=-=SIGNALS=-=-=-=-=-=-=-=-=-=-=-=*/

void				handle_sigint(int sig);
void				handle_sigquit(int sig);

// NEEDS TO BE READAPTED TO ANNA'S CODE
// so all info gonna be stored at parser->cmd[i] and next node when 
//encountering pipes or redirections and so.
/*-=-=-=-=-=-=-=-=-=-=-=BUILTINS=-=-=-=-=-=-=-=-=-=-=-=*/
//
int					is_builtin_execute(t_parser *token, t_env **env, int *error);
int					built_ls(void);
int					built_grep(void);
t_env				*load_env(char **envp);
int					print_env_lst(t_env *env);
int					print_hidden_lst(t_env *env);
bool				env_exist(t_env *env, char *str);
bool	env_no_value(char *var);
char	*get_til_equal(char *var);
char	*equal_til_end(char	*var);
char	*get_home(t_env *env);
/*-=-=-=-=-=-=-=-=-=-=-=ENV_TOOLS=-=-=-=-=-=-=-=-=-=-=-=*/
void	shell_level(t_env **env);
void	add_env_shell(t_env **env);
void	del_env(t_parser *parser, t_env **env, int i);
void	add_env(t_parser *parser, t_env **env, int i);
void	edit_env(t_parser *parser, t_env **env, int i);
char	*expand_str_plus(char *str, t_env *env);
char	*clear_spaces(char *str);

/*				HEREDOCK		*/
int	heredock_check(t_parser *parser);
int	build_heredock(char *path, char *where);
int	start_heredock(t_redir *sup,int i);
/*-=-=-=-=-=-=-=-=EXPANSOR=-=-=-=-=-=-=-=-=-=-=*/

char				*find_dollar(char *str, t_env *env, int	exit_code);

/*-=-=-=-=-=-=-=-=-=-=-=TOOLS=-=-=-=-=-=-=-=-=-=-=*/
int					errno_printer(char *com, char *error_txt, char *asked);
int					errno_printer_2(char *com, char *error_txt, char *asked, int val);
char				*trim_after(char *str, char c);
char				*trim_bef(char *str, char c);
char				*clear_quotes(char *str, t_env *env, int exit_code);
int					is_poss_char(char c);
long long	ft_check_arg_is_num(char *argv);
long long	ft_check_max_min(char *argv);
int	errno_printer_export(char *com, char *error_txt, char *asked);

/*==============================ANNA======================================*/
void	ft_error(int ernu, char *msg, int *error);
void	ft_other_error(char *msg, int *error, int num);
void	free_all(t_parser *data, char **str);
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-LEXER-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void				lexer(char *line);
void				free_matrix(char **matrix, size_t p);
void				*my_malloc(size_t bytes);
int					is_quote(char letter);
int					is_space(char c);
int					is_sign(char c);
int					quote_situation(char *c);
int					arg_count(char *line, int i, int wc);
t_lexer				*ft_lexer(char *line);
char				**new_split(char *line, int wc, int i, int k);
void				sign_situation(char *line, char **split, int *j, int *i);
char				*ft_substri(const char *str, int start, int len);
void				get_word(int k, int *i, char *line, char **split);
char				*ft_strncpy(char *s1, char *s2, int n);
char				*token(char *dest, char *src, int len);
void				sign(t_lexer *lexer, char *slpit);
t_lexer				*tokenize(t_lexer *lexer, char **split);
t_lexer				*lexer_creator(void);
void				break_free(t_lexer	*lexer);

/*-=-=-=-=-=-=-==-=-=-==-=-=-PARSER-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int					cmd_count(t_lexer *lexer);
char				**parser_split(t_lexer *lexer, t_parser *parser);
t_parser			*ft_parser(t_lexer *lexer, int *error);
t_sign				get_sign(char *sign);
t_parser			*parser_creator(void);
void				error_parser(char *msg);
void				parser_content(t_lexer *lexer, t_parser *parser, int i, int	*error);
t_redir				*redir_creator();
void				first_redir(t_lexer *lexer, t_parser *parser, int *error);
char				**commands(t_lexer *lexer);

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=EXECUTOR-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

typedef	struct s_pipe
{
	int		num_cmds;
	int		std_in;
	int		std_out;
	int		fd[2];
	char	*path;
	char	**paths;
	pid_t	*children;
}			t_pipe;

int			parser_size(t_parser *parser);
char		*ft_strjoini(char const *s1, char const *s2);
void		exec_error(char	*message);
int			env_size(t_env *env);
char		**env_to_char(t_env	*env);
void		redir_manager(t_parser *parser);
int			find_last_redir_in(t_redir *redir);
int			find_last_redir_out(t_redir *redir);
int			execute(t_parser *parser, t_env	**envi, int *error);
void		child_process(t_pipe *pipex, t_parser *parser, t_env **envi, int *error);
void		fd_situation(t_pipe *pipex, t_parser *parser);
void		parse_path(char **envp, t_pipe *pipex);
char		*find_command(t_pipe *pipex, t_parser *parser, int *error);
int			matrix_size(char **pars_cmds);
void		free_parser(t_parser *parser);
void		free_parent(t_pipe *pipex);
int			error_child(int ernu, char *msg, int excode);
t_parser 	*ahorramos_lineas(t_parser *parser, int *i, t_lexer *lexer);
int			is_builtin_or_not(t_parser *parser);
void		exec_start(t_pipe *pipex, t_parser *parser);
void		exec_finish(t_pipe *pipex);
void		waiting(t_pipe *pipex, int *status, int num_cmds);
void		execute_fin(t_parser *parser);
int			is_lonely_builtin(t_parser *parser, t_pipe *pipex, t_env **envi, int *error);
void		making_kids(t_parser *parser, t_pipe *pipex, t_env **envi, int *error);
void		get_token(t_parser *parser, t_lexer *lexer, t_redir *tmp);


#endif