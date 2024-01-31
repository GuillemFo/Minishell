/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/31 16:25:38 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	built_env(t_parser *token)
{
	
	return (0);
}

int	built_echo(t_parser *token)
{
	int	flag;
	ft_printf("entered echo\n");

	flag = 1;
	if (ft_strncmp("-n" ,token->content[1], 3) == 0)
	{
		flag = 0;
		ft_putstr_fd(token->content[2], STDOUT_FILENO);
	}
	else if (flag == 1)
	{
		ft_putstr_fd(token->content[1], STDOUT_FILENO);
		write(1, "\n", 1);
	}
	return (0);
}

int	built_cd(t_parser *token)
{
	if (chdir(token->content[1]) < 0)
		errno_printer(token->content[0], strerror(errno), token->content[1]);
	return (0);
}

int	built_pwd()//(t_parser *token)
{
	ft_printf("%s\n", getcwd(NULL, MAXPATHLEN));
	return (0);
}


int	is_builtin(t_parser *token) 
{
	if (token->content)//need to check til when we loop.
	{
		if (ft_strncmp("echo", token->content[0], 5) == 0)
			built_echo(token);
		else if (ft_strncmp("cd", token->content[0], 3) == 0)
			built_cd(token);
		else if (ft_strncmp("pwd", token->content[0], 4) == 0)
			built_pwd();//(token);
		else if (ft_strncmp("env", token->content[0], 4) == 0)
			built_env(token);
		else if (ft_strncmp("exit", token->content[0], 5))
		token = token->next;
	}
	// else if (token->content == "export")
	return (0);
}

// Implement the builtins:
// 						◦ echo with option -n
// 						◦ cd with only a relative or absolute path
// 						◦ pwd with no options
// 						◦ export with no options
// 						◦ unset with no options
// 						◦ env with no options or arguments
// 						◦ exit with no options