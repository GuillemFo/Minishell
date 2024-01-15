/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:06 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/15 13:17:45 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
t_lexer 	lexer(char *str)
{

	return ();
}
*/









int	main(int ac, char **av)
{
	char *str;
	(void)ac;
	(void)av;
	str = readline("minishell: ");
	while (str)
	{
		add_history(str);
		//lexer(str);
		printf("%s\n", str);
		str = readline("minishell: ");
	}
}
//Intentar crear un programa que funcione de forma infinita y sea capaz de imprimir lo que le pase
//Probar a usar el readline
//Hay que incluir librerias de readline en makefile y entender como funciona
