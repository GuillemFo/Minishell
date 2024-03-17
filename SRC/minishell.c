/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/03/17 08:59:40 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_parser	*clean_input(t_parser *parser, t_env *env, int exit_code)
{
	int	i;
	t_parser	*iter;
	iter = parser;
	while (iter)
	{
		i = 0;
		if (iter->cmd[i])
		{
			while (iter->cmd[i])
			{
				iter->cmd[i] = clear_quotes(iter->cmd[i], env, exit_code);
				i++;
			}
		}
		iter = iter->next;
	}
	return (parser);
}



int	main(int ac, char **av, char **envp)
{
	t_parser	*data;
	t_lexer		*input;		
	t_env		*env;
	int			error;
	int			exit_code;
	
	exit_code = 0;
	(void)error;
	char *str;
	(void)av;
	if (ac != 1)
		return(1);
	env = load_env(envp);
	env = shell_level(env);
	
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint); //reminder that leaks atexit will kill program if use ctrl + c
	signal(SIGQUIT, handle_sigquit);
	str = readline(C_G "minishell: " C_RESET);
	while (str)
	{
		error = 0;
		add_history(str);
		if (str) 
		{
			input = ft_lexer(str);
			data = ft_parser(input, &error);
			if (!error && data)
    		{
				data = clean_input(data, env, exit_code);
				heredock_check(data);
				error = execute(data, &env, &error);
			}
			exit_code = error;
		free_all(data, &str);
		}
	}
	return (exit_code);
}
