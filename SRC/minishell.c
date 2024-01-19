/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:06 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/19 12:58:04 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//the loop: while (token->next != NULL && token->sign == NONE)

t_parser *test_load(void)
{
    t_parser *token;
    token = malloc(sizeof(t_parser));
    token->content = malloc(3 * sizeof(char*));
    token->content[0] = strdup("ls");
    token->content[1] = strdup("-l");
    token->content[2] = NULL;
    token->sign = NONE;
    token->next = malloc(sizeof(t_parser));
    token->next->content = malloc(3 * sizeof(char*));
    token->next->content[0] = strdup("grep");
    token->next->content[1] = strdup("txt");
    token->next->content[2] = NULL;
    token->next->sign = PIPE;
    token->next->next = malloc(sizeof(t_parser));
    token->next->next->content = NULL;
    token->next->next->sign = NONE;
    token->next->next->next = NULL;

    return (token);
}





int	main(int ac, char **av)
{
	t_parser	*data;
	char *str;
	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	data = test_load();
	ft_printf("content{%s}\n", data->content[0]);
	is_builtin(data);
	str = readline("minishell: ");
	while (str)
	{
		add_history(str);
		str = readline("minishell: ");
	}
}
//Intentar crear un programa que funcione de forma infinita y sea capaz de imprimir lo que le pase
//Probar a usar el readline
//Hay que incluir librerias de readline en makefile y entender como funciona
