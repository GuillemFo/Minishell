/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:06 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/19 09:56:04 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum	e_type
{
	NONE = 0,
	PIPE,
	LESS
}				t_type;

typedef struct s_lexer
{
	char			**content;
	t_type			sign;
	struct s_lexer	*next;
}					t_lexer;

t_lexer	*test_load(void) //the loop: while (token->next != NULL && token->sign = NONE)
{
    t_lexer *token = malloc(sizeof(t_lexer));
    token->content = (char *[]){"ls", "-l", NULL};
    token->sign = NONE;
    token->next = malloc(sizeof(t_lexer));
    token->next->content = (char *[]){"grep", "txt", NULL};
    token->next->sign = PIPE;
    token->next->next = NULL;
	return (token);
}






int	main(int ac, char **av)
{
	t_lexer	*data;
	char *str;
	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	data = test_load();
	str = readline("minishell: ");
	while (str)
	{
	//	bi_gen(str);
		add_history(str);
		//printf("%s\n", str);
		str = readline("minishell: ");
	}
}
//Intentar crear un programa que funcione de forma infinita y sea capaz de imprimir lo que le pase
//Probar a usar el readline
//Hay que incluir librerias de readline en makefile y entender como funciona
