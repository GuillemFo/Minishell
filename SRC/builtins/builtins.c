/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/19 09:56:43 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*

int	bi_echo(t_lexer *lexer)
{
	int	flag;

	flag = 1;
	if (lexer->)
		flag = 0;
	ft_putstr_fd(lexer->content, STDOUT_FILENO);
	if (flag == 1)
		write(1, "\n", 1);
	return (1);
}

int	bi_gen(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp("exit", str, 5) == 0)
		exit(0);
	else if (ft_strncmp("echo ", str, 5) == 0)
		bi_echo(str);
	// else if (lexer->content == "cd")
	// else if (lexer->content == "pwd")
	// else if (lexer->content == "export")
	return (i);
}

// Implement the builtins:
// 						◦ echo with option -n
// 						◦ cd with only a relative or absolute path
// 						◦ pwd with no options
// 						◦ export with no options
// 						◦ unset with no options
// 						◦ env with no options or arguments
// 						◦ exit with no options
*/