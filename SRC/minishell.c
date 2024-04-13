/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:48:05 by codespace         #+#    #+#             */
/*   Updated: 2024/04/13 17:21:19 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*clean_input(t_parser *parser, t_env *env, int exit_code)
{
	int			i;
	t_parser	*iter;
	t_redir		*tmp;
	char		*tmp2;
	char		*tmp_ex;

	tmp_ex = NULL;
	iter = parser;
	if (iter != NULL)
	{
		while (iter)
		{
			i = 0;
			while (iter->cmd && iter->cmd[i] != NULL && iter->cmd[i][0] != '\0')
			{
				tmp2 = clear_quotes(&(iter->cmd[i]), env, exit_code, tmp_ex);
				free(iter->cmd[i]);
				iter->cmd[i] = ft_strdup(tmp2);
				free(tmp2);
				i++;
			}
			tmp = iter->redir;
			while (tmp && tmp->dest)
			{
				tmp2 = clear_quotes(&(tmp->dest), env, exit_code, tmp_ex);
				free(tmp->dest);
				tmp->dest = tmp2;
				tmp = tmp->next;
			}
			iter = iter->next;
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

int	main(int ac, char **av, char **envp)
{
	t_parser	*data;
	t_lexer		*input;		
	t_env		*env;
	t_errors	err;

	(void)av;
	if (ac != 1)
		return (1);
	env = NULL;
	env = inition_signals_env(&err.error, &err.exit_code, envp, env);
	err.str = readline(C_G "minishell: " C_RESET);
	if (err.str)
	{
		while (1)
		{
			add_history(err.str);
			if (err.str)
			{
				err.error = 0;
				input = ft_lexer(err.str);
				data = ft_parser(input, &err.error);
				if (!err.error && data)
					executing(data, env, &err);
				err.str = freestyle(err.error, &err.exit_code, data, err.str);
				if (!err.str)
					break ;
			}
		}
	}
	free_env(&env);
	return (err.exit_code);
}
