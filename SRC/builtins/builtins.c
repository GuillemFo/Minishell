/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/22 10:41:18 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	built_env(t_parser *token)
{
	ft_printf("%s\n", getenv(token->content[1]));
	return (1);
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
	return (1);
}

int	built_cd(t_parser *token)
{
	ft_printf("entered cd\n");
	ft_printf("1\n");
	ft_printf("%s\n", getcwd(NULL, MAXPATHLEN));
	if (chdir(token->content[1]) == -1)
		return (ft_printf("Path not found\n")); // temporal error
	ft_printf("2\n");
	ft_printf("%s\n", getcwd(NULL, MAXPATHLEN));

	return (2);
}

int	built_pwd(t_parser *token)
{
	if (token->content[1] == NULL)
		ft_printf("%s\n", getcwd(NULL, MAXPATHLEN));
	else
		ft_printf("pwd: too many arguments\n");
	return (2);
}


int	is_builtin(t_parser *token)
{
	while (!(token == NULL))
	{
		if (ft_strncmp("echo", token->content[0], 4) == 0)
			built_echo(token);
		else if (ft_strncmp("cd", token->content[0], 2) == 0)
			built_cd(token);
		else if (ft_strncmp("pwd", token->content[0], 3) == 0)
			built_pwd(token);
		else if (ft_strncmp("env", token->content[0], 3) == 0)
			built_env(token);
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