/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:20:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/31 16:30:39 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <../libft/libft.h>
# include <errno.h>
# include <history.h>
# include <readline.h>
# include <signal.h>
# include <string.h>
# include <sys/param.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdbool.h>

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

int	is_builtin(t_parser *token);
int	built_ls();
int	built_grep();
t_env	*load_env(char **envp);
int		print_env_lst(t_env *env)

/*-=-=-=-=-=-=-=-=-=-=-=TOOLS=-=-=-=-=-=-=-=-=-=-=*/
int	errno_printer(char *com, char *error_txt, char *asked);

#endif