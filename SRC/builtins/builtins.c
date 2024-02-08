/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/08 11:38:31 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_exit()
{
	return (0);
}
// int		builtin_export(t_parser *token, t_env *env)
// {
	// if (env_exist(env, token) == false)		//might have a chaos of modifiable pointers and directions
		// env = add_env(token, env);			//pending to check :)
											// 
	// return (0);
// }
// 
// int	builtin_unset(t_parser *token, t_env *env)
// {
	// env  = del_env(token, env);
	// return (0);
// }

int	built_env(t_env *env)
{
	print_env_lst(env);
	return (0);
}

int	built_echo(t_parser *token)
{
	int	flag;

	flag = 1;
	if (ft_strncmp("-n" ,token->cmd[1], 3) == 0)
	{
		flag = 0;
		ft_putstr_fd(token->cmd[2], STDOUT_FILENO);
	}
	else if (flag == 1)
	{
		ft_putstr_fd(token->cmd[1], STDOUT_FILENO);
		write(1, "\n", 1);
	}
	return (0);
}

int	built_cd(t_parser *token)
{
	if (chdir(token->cmd[1]) < 0)
		errno_printer(token->cmd[0], strerror(errno), token->cmd[1]);
	return (0);
}

int	built_pwd()//(t_parser *token)
{
	ft_printf("%s\n", getcwd(NULL, MAXPATHLEN));
	return (0);
}


int	is_builtin(t_parser *token, t_env *env) 
{
	if (token->cmd)//need to check til when we loop.
	{
		if (ft_strncmp("echo", token->cmd[0], 5) == 0)
			built_echo(token);
		else if (ft_strncmp("cd", token->cmd[0], 3) == 0)
			built_cd(token);
		else if (ft_strncmp("pwd", token->cmd[0], 4) == 0)
			built_pwd();//(token);
		else if (ft_strncmp("env", token->cmd[0], 4) == 0)
			built_env(env);
		else if (ft_strncmp("exit", token->cmd[0], 5) == 0)
			builtin_exit();
		// else if (ft_strncmp("export", token->cmd[0], 7) == 0)
		// 	builtin_export(token, env);
		// else if (ft_strncmp("unset", token->cmd[0], 6) == 0)
		// 	builtin_unset(token, env);
		token = token->next;
	}
	return (0);
}

