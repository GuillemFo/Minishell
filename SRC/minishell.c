/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:06 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/28 09:19:15 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function will be used to clean the data from all nodes with info.
t_parser	*clean_input(t_parser *parser, t_env *env)			//data = clean_input(data, env);
{
	int	i;
	(void)env;
	t_parser	*iter;
	iter = parser;
	while (iter)
	{
		i = 0;
		if (iter->cmd[i])
		{
			while (iter->cmd[i])
			{
			printf("cmd1: %s\n\n", iter->cmd[i]);
				iter->cmd[i] = clear_quotes(iter->cmd[i]);
			printf("cmd2: %s\n\n", iter->cmd[i]);
				//iter->cmd[i] = find_dollar(iter->cmd[i], env);
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
	
	(void)error;
	char *str;
	(void)av;
	if (ac != 1)
		return(1);
	env = load_env(envp);
	
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint); //reminder that leaks atexit will kill program if use ctrl + c
	signal(SIGQUIT, handle_sigquit);
	str = readline(C_G "minishell: " C_RESET);
	while (str)
	{
		add_history(str);
		if (str)
		{
			input = ft_lexer(str);
			data = ft_parser(input);
			data = clean_input(data, env);
			execute(data, env);
		}
		free_parser(data);
		free(str);
		str = readline(C_G "minishell: " C_RESET);
		if (str != NULL)
		{
			input = ft_lexer(str);
			data = ft_parser(input);
			data = clean_input(data, env);
			is_builtin(data, env);
		}
	}
}
