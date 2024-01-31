/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:06 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/31 20:44:20 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//the loop: while (token->next != NULL)

t_parser *test_load(void)
{
    t_parser *token;
    token = malloc(sizeof(t_parser));
    token->content = malloc(3 * sizeof(char*));
    token->content[0] = ft_strdup("env");
    //token->content[1] = ft_strdup("");
    token->content[1] = NULL;
    token->sign = NONE;
    token->next = NULL;

    return (token);
}

//token->next->content = NULL; if | encountered.




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
	is_builtin(data, env);
	str = readline("minishell: ");
	while (str)
	{
		add_history(str);
		free(str);
		str = readline("minishell: ");
	}
}
//Intentar crear un programa que funcione de forma infinita y sea capaz de imprimir lo que le pase
//Probar a usar el readline
//Hay que incluir librerias de readline en makefile y entender como funciona
