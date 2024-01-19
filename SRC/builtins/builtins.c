/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/19 13:00:19 by gforns-s         ###   ########.fr       */
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

int	built_ls()
{
	ft_printf("entered ls\n");
	return (1);
}

int	built_grep()
{
	ft_printf("entered grep\n");
	return (2);
}


int	is_builtin(t_parser *token)
{
	while (!(token->content == NULL && token->sign == NONE))
	{
		ft_printf("in:{%s}\n", token->content[0]);
		if (ft_strncmp("ls", token->content[0], 2) == 0)
			built_ls();
		else if (ft_strncmp("grep", token->content[0], 4) == 0)
			built_grep();
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