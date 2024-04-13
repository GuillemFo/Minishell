/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:48:05 by codespace         #+#    #+#             */
/*   Updated: 2024/04/13 18:23:40 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*clean_input(t_parser *parser, t_env *env, int exit_code)
{
	int			i;
	t_parser	*itr;
	t_redir		*tmp;
	char		*tmp2;

	itr = parser;
	if (itr != NULL)
	{
		while (itr)
		{
			i = -1;
			while (itr->cmd && itr->cmd[++i] != NULL && itr->cmd[i][0] != '\0')
			{
				tmp2 = clear_quotes(&(itr->cmd[i]), env, exit_code);
				free(itr->cmd[i]);
				itr->cmd[i] = ft_strdup(tmp2);
				free(tmp2);
			}
			tmp = itr->redir;
			while (tmp && tmp->dest)
				cl_quotes_s(&tmp, &tmp2, env, exit_code);	//test if heredock leaks with multiple ones, cat -e << EOF << EOF1 << EOF2
			itr = itr->next;
		}
	}
	return (parser);
}

t_env	*inition_signals_env(int *error, int *exit_code, char **envp, t_env *env)
{
	*error = 0;
	*exit_code = 0;
	env = load_env(envp);
	shell_level(&env);
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	return (env);
}

void	executing(t_parser *data, t_env *env, t_errors *err)
{
	data = clean_input(data, env, err->exit_code);
	heredock(&data, env, err->exit_code);
	err->error = execute(data, &env, &err->exit_code);
}


char *freestyle(int error, int *exit_code, t_parser *data, char *str)
{
	*exit_code = error;
	free_parser(data);
	free(str);
	str = NULL;
	return (readline(C_G "minishell: " C_RESET));
}

void my_add_history(char *str, char **av)
{
	(void)av;	
	add_history(str);
}

int	returning(t_env *env, int exit_code)
{
	free_env(&env);
	return (exit_code);
}

t_lexer	*function(int *error, char *str)
{
	*error = 0;
	return (ft_lexer(str));
}

char	*beginning(t_env **env, int *error, int *exit_code, char **envp)
{
	*env = inition_signals_env(error, exit_code, envp, *env);
	return (readline(C_G "minishell: " C_RESET));
}

int	main(int ac, char **av, char **envp)
{
	t_parser	*data;
	t_env		*env;
	t_errors	err;

	if (ac != 1)
		return (1);
	env = NULL;
 	err.str = beginning(&env, &err.error, &err.exit_code, envp);
	if (err.str)
	{
		while (1)
		{
			my_add_history(err.str, av);
			if (err.str)
			{
				data = ft_parser(function(&err.error, err.str), &err.error);
				if (!err.error && data)
					executing(data, env, &err);
				err.str = freestyle(err.error, &err.exit_code, data, err.str);
				if (!err.str)
					break ;
			}
		}
	}
	return (returning(env, err.exit_code));
}
