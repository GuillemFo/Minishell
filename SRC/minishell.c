/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/03/28 16:19:05 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_parser	*clean_input(t_parser *parser, t_env *env, int exit_code)
{
	int	i;
	t_parser	*iter;
	char *str;

	t_redir	*tmp;
	iter = parser;
	if (iter != NULL)
	{	
		while (iter)
		{
			i = 0;
			while (iter->cmd && iter->cmd[i] != NULL)
			{
				str = clear_quotes(iter->cmd[i], env, exit_code);
				free(iter->cmd[i]);
				iter->cmd[i] = str;
				i++;
			}
			tmp = iter->redir;
			while (tmp && tmp->dest)
			{
				str = clear_quotes(tmp->dest, env, exit_code);
				free(tmp->dest);
				tmp->dest = str;
				tmp = tmp->next;
			}
			iter = iter->next;
		}
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
	error = 0;
	char *str;
	(void)av;
	if (ac != 1)
		return(1);
	env = load_env(envp);
	shell_level(&env);
	
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint); //reminder that leaks atexit will kill program if use ctrl + c
	signal(SIGQUIT, handle_sigquit);
	str = readline(C_G "minishell: " C_RESET);
	if (str)
	{
		while (1)
		{
			add_history(str);
			if (str) 
			{
				error = 0;
				input = ft_lexer(str);
				data = ft_parser(input, &error);
				if (!error && data)
				{
					data = clean_input(data, env, error);
					heredock(data, env, exit_code);
					error = execute(data, &env, &exit_code);
					error = exit_code;
				}
				exit_code = error;
				free_all(data);
				free(str);
				str = NULL;
				str = readline(C_G "minishell: " C_RESET);
				if (!str)
					break;
				break;
			}
		}
	}
	free_env(&env);
	return (exit_code);
}
