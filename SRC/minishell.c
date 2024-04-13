/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:48:05 by codespace         #+#    #+#             */
/*   Updated: 2024/04/13 16:10:09 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*clean_input(t_parser *parser, t_env *env, int exit_code)
{
	int			i;
	t_parser	*iter;
	t_redir		*tmp;
	char		*tmp2;

	iter = parser;
	if (iter != NULL)
	{
		while (iter)
		{
			i = -1;
			while (iter->cmd && iter->cmd[++i] != NULL && iter->cmd[i][0] != '\0')
			{
				tmp2 = clear_quotes(&(iter->cmd[i]), env, exit_code);
				free(iter->cmd[i]);
				iter->cmd[i] = ft_strdup(tmp2);
				free(tmp2);
				i++;
			}
			tmp = iter->redir;
			while (tmp && tmp->dest)
				cl_quotes_s(tmp, &tmp2, env, exit_code);
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
	char		*str;

	exit_code = 0;
	error = 0;
	(void)av;
	if (ac != 1)
		return (1);
	env = load_env(envp);
	shell_level(&env);
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
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
					data = clean_input(data, env, exit_code);
					heredock(&data, env, exit_code);
					//printf("hola\n");
					error = execute(data, &env, &exit_code);
					exit_code = error;
				}
				exit_code = error;
				free_parser(data);
				free(str);
				str = NULL;
				str = readline(C_G "minishell: " C_RESET);
				if (!str)
					break ;
			}
		}
	}
	free_env(&env);
	return (exit_code);
}
