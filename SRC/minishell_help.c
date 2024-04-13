/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:29:41 by codespace         #+#    #+#             */
/*   Updated: 2024/04/13 16:35:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*inition_signals_env(int *error, int *exit_code, char **envp,
		t_env *env)
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

char	*freestyle(int error, int *exit_code, t_parser *data, char *str)
{
	*exit_code = error;
	free_parser(data);
	free(str);
	str = NULL;
	return (readline(C_G "minishell: " C_RESET));
}

void	my_add_history(char *str, char **av)
{
	(void)av;
	add_history(str);
}

int	returning(t_env *env, int exit_code)
{
	free_env(&env);
	return (exit_code);
}
