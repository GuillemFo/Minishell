/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:11:52 by codespace         #+#    #+#             */
/*   Updated: 2024/04/13 16:36:28 by codespace        ###   ########.fr       */
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

typedef struct s_errors
{
	int			error;
	int			exit_code;
	char		*str;
}				t_errors;		

typedef enum e_sign
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
	struct s_redir	*next;
}					t_redir;

typedef struct s_parser
{
	char			**cmd;
	t_redir			*redir;
	struct s_parser	*next;
}					t_parser;

typedef struct s_pipe
{
	int				num_cmds;
	int				std_in;
	int				std_out;
	int				fd[2];
	char			*path;
	char			**paths;
	pid_t			*children;
}					t_pipe;

typedef struct s_tmp
{
	char			*tmp_ex;
	char			*tmp_bef;
	char			*tmp_cont;
	char			*tmp_after;
	char			*res;
	char			*tmp_help;
	char			c;
}					t_tmp;

/*-=-=-=-=-=-=-=-=-=-=-=MAIN=-=-=-=-=-=-=-=-=-=-=-=*/

t_env				*inition_signals_env(int *error, int *exit_code,
						char **envp, t_env *env);
void				executing(t_parser *data, t_env *env, t_errors *err);
char				*freestyle(int error, int *exit_code, t_parser *data,
						char *str);
void				my_add_history(char *str, char **av);
int					returning(t_env *env, int exit_code);

/*-=-=-=-=-=-=-=-=-=-=-=SIGNALS=-=-=-=-=-=-=-=-=-=-=-=*/

void				handle_sigint(int sig);
void				handle_sigquit(int sig);
void				handle_sigint_child(int sig);

/*-=-=-=-=-=-=-=-=-=-=-=QUOTES=-=-=-=-=-=-=-=-=-=-=-=*/

t_parser			*clean_input(t_parser *parser, t_env *env, int exit_code);
void				cl_quotes_s(t_redir **tmp, char **tmp2, t_env *env,
						int exit_code);
char				*clear_quotes(char **str, t_env *env, int exit_code);
void				clear_q_1(t_tmp *tmp, char **res, t_env *env,
						int exit_code);
void				clear_q_2(t_tmp *tmp, char **res);
void				clear_q_3(t_tmp *tmp, t_env *env, int exit_code);
void				clear_q_4(t_tmp *tmp, t_env *env, int exit_code);
void				clear_q_5(t_tmp *tmp);
void				clear_q_6(t_tmp *tmp);
void				clear_q_7(t_tmp *tmp, char **res, t_env *env,
						int exit_code);
void				clear_q_8(t_tmp *tmp, char **res, t_env *env,
						int exit_code);
void				multi_q(t_tmp *tmp, t_env *env, int exit_code);
char				has_quotes(char *str);
char				*cnt_b_q(char *str, char c);
char				*cnt_in_q(char *str, char c);
char				*cnt_aft_q(char *str, char c);
int					errno_printer_quotes(char *com, char *error_txt,
						int val);
/*-=-=-=-=-=-=-=-=-=-=-=BUILTINS=-=-=-=-=-=-=-=-=-=-=-=*/

int					is_builtin_execute(t_parser *token, t_env **env,
						int *error);
int					built_ls(void);
int					built_grep(void);
t_env				*load_env(char **envp);
int					print_env_lst(t_env *env);
int					print_hidden_lst(t_env *env);
bool				env_exist(t_env *env, char *str);
bool				env_no_value(char *var);
char				*get_til_equal(char *var);
char				*equal_til_end(char	*var);
char				*get_home(t_env *env);
int					builtin_export(t_parser *parser, t_env **env, int ret);
int					builtin_unset(t_parser *parser, t_env **env);
int					builtin_exit(t_parser *parser, int *error);
int					check_is_n(char *str);
t_env				**get_pwd(t_env **env);
int					built_pwd(void);
t_env				**get_old_pwd(t_env **env);

/*-=-=-=-=-=-=-=-=-=-=-=ENV_TOOLS=-=-=-=-=-=-=-=-=-=-=-=*/

void				shell_level(t_env **env);
void				add_env_shell(t_env **env);
void				del_env(t_parser *parser, t_env **env, int i);
void				add_env(t_parser *parser, t_env **env, int i);
void				edit_env(t_parser *parser, t_env **env, int i, char *tmp2);
bool				env_has_equal(char *var);
void				set_null_hidden(t_env *iter);

/*				HEREDOCK		*/

int					heredock(t_parser **parser, t_env *env, int exit_code);

/*-=-=-=-=-=-=-=-=EXPANSOR=-=-=-=-=-=-=-=-=-=-=*/

char				*fnd_dllr(char *str, t_env *env, int exit_code);
char				*fnd_dllr_var(char *str, int exit_code);
char				*expand_str_extra(char *str, int exit_code, int *x);

/*-=-=-=-=-=-=-=-=-=-=-=TOOLS=-=-=-=-=-=-=-=-=-=-=*/
int					errno_printer_home(char *com, char *asked);
int					errno_printer(char *com, char *error_txt, char *asked);
int					errno_printer_2(char *com, char *error_txt, char *asked,
						int val);
char				*trim_after(char *str, char c);
char				*trim_bef(char *str, char c);
char				*trim_after_dlr(char *str, char c);

int					is_poss_char(char c);
long long			ft_check_arg_is_num(char *argv);
long long			ft_check_max_min(char *argv);
int					errno_printer_export(char *com, char *error_txt,
						char *asked);
int					errno_printer_3(char *com, char *error_txt,
						char *asked, int val);
void				*free_env(t_env **env);
long long			ft_atoll(char *str);
void				*ft_free_split(char **s);
void				three_free(void *one, void *two, void *three);

/*==============================ANNA======================================*/
void				ft_error(int ernu, char *msg, int *error);
void				ft_other_error(char *msg, int *error, int num);
void				free_all(t_parser *data);
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-LEXER-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
int					is_redir(char c);
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
void				parser_content(t_lexer *lexer, t_parser *parser, int i,
						int	*error);
t_redir				*redir_creator(void);
void				first_redir(t_lexer *lexer, t_parser *parser, int *error);
char				**commands(t_lexer *lexer);

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=EXECUTOR-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

int					status_situation(int status);
int					parser_size(t_parser *parser);
char				*ft_strjoini(char const *s1, char const *s2);
void				exec_error(char	*message);
int					env_size(t_env *env);
char				**env_to_char(t_env	*env);
void				redir_manager(t_parser *parser);
int					find_last_redir_in(t_redir *redir);
int					find_last_redir_out(t_redir *redir);
int					execute(t_parser *parser, t_env	**envi, int *error);
void				child_process(t_pipe *pipex, t_parser *parser,
						t_env **envi, int *error);
void				fd_situation(t_pipe *pipex, t_parser *parser);
void				parse_path(char **envp, t_pipe *pipex);
char				*find_command(t_pipe *pipex, t_parser *parser, int *error);
int					matrix_size(char **pars_cmds);
void				free_parser(t_parser *parser);
void				free_parent(t_pipe *pipex);
int					error_child(int ernu, char *msg, int excode);
t_parser			*parser_update(t_parser *parser, int *i, t_lexer *lexer);
int					is_builtin_or_not(t_parser *parser);
void				exec_start(t_pipe *pipex, t_parser *parser);
void				exec_finish(t_pipe *pipex);
void				waiting(t_pipe *pipex, int *status, int num_cmds);
void				execute_fin(t_parser *parser);
int					is_lonely_builtin(t_parser *parser, t_pipe *pipex,
						t_env **envi, int *error);
void				making_kids(t_parser *parser, t_pipe *pipex,
						t_env **envi, int *error);
void				get_token(t_parser *parser, t_lexer *lexer, t_redir *tmp);

#endif