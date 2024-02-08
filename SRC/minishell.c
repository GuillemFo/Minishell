/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:06 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/08 11:47:14 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//the loop: while (token->next != NULL)

t_parser *test_load(void)
{
    t_parser *parser;
    parser = malloc(sizeof(t_parser));
    parser->cmd = malloc(3 * sizeof(char*));
    parser->cmd[0] = ft_strdup("echo");
    parser->cmd[1] = ft_strdup("expand this $USER $USER");
	//parser->cmd[2] = ft_strdup(" ");
    parser->cmd[2] = NULL;
    parser->next = NULL;

    return (parser);
}

//token->next->cmd = NULL; if | encountered.




int	main(int ac, char **av, char **envp)
{
	t_parser	*data;
	t_env		*env;
	char *str;
	(void)ac;
	(void)av;
	env = load_env(envp);
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint); //reminder that leaks atexit will kill program if use ctrl + c
	signal(SIGQUIT, handle_sigquit);
	data = test_load();
	data->cmd[1] = find_dollar(data->cmd[1], env);
	is_builtin(data, env);
	str = readline(C_G "minishell: " C_RESET);
	while (str)
	{
		add_history(str);
		free(str);
		str = readline(C_G "minishell: " C_RESET);
	}
}
//Intentar crear un programa que funcione de forma infinita y sea capaz de imprimir lo que le pase
//Probar a usar el readline
//Hay que incluir librerias de readline en makefile y entender como funciona
