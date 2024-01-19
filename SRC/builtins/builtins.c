/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/19 13:44:34 by gforns-s         ###   ########.fr       */
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
*/

int	built_echo(t_parser *token)
{
	int	flag;
	ft_printf("entered echo\n");

	flag = 1;
	if (ft_strncmp("-n" ,token->content[1], 2))
	{
		flag = 0;
		ft_putstr_fd(token->content[2], STDOUT_FILENO);
	}
	else if (flag == 1)
	{
		ft_putstr_fd(token->content[1], STDOUT_FILENO);
		write(1, "\n", 1);
	}
	return (1);
}

int	built_cd()
{
	ft_printf("entered cd\n");
	return (2);
}


int	is_builtin(t_parser *token)
{
	while (!(token->content == NULL && token->sign == NONE))
	{
		if (ft_strncmp("echo", token->content[0], 4) == 0)
			built_echo(token);
		else if (ft_strncmp("cd", token->content[0], 2) == 0)
			built_cd();
		token = token->next;
	}
	// else if (token->content == "pwd")
	// else if (token->content == "export")
	return (3);
}

// Implement the builtins:
// 						◦ echo with option -n
// 						◦ cd with only a relative or absolute path
// 						◦ pwd with no options
// 						◦ export with no options
// 						◦ unset with no options
// 						◦ env with no options or arguments
// 						◦ exit with no options