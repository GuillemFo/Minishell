/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:20:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/06 11:06:59 by gforns-s         ###   ########.fr       */
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

typedef enum	e_type
{
	NONE = 0,
	PIPE,
	LESS
}				t_type;

typedef struct s_parser
{
	char			**content;
	t_type			sign;
	struct s_parser	*next;
}					t_parser;



void	handle_sigint(int sig);
void	handle_sigquit(int sig);

/*-=-=-=-=-=-=-=-=-=-=-=BUILTINS=-=-=-=-=-=-=-=-=-=-=-=*/

int	is_builtin(t_parser *token, t_env *env);
int	built_ls();
int	built_grep();
t_env	*load_env(char **envp);
int		print_env_lst(t_env *env);
bool		env_exist(t_env *env, t_parser *token);
bool		env_exist_2(t_env *env, char *name);
t_env	*del_env(t_parser *token, t_env *env);
t_env	*add_env(t_parser *token, t_env *env);
/*-=-=-=-=-=-=-=-=-=-=-=TOOLS=-=-=-=-=-=-=-=-=-=-=*/
int	errno_printer(char *com, char *error_txt, char *asked);

#endif