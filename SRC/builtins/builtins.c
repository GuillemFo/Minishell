/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/03 17:44:36 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_exit()
{
	return (0);
}



// int		builtin_export(t_parser *parser, t_env *env)
// {
	// if (env_exist(env, parser) == false)		//might have a chaos of modifiable pointers and directions
		// env = add_env(parser, env);			//pending to check :)
											// 
	// return (0);
// }



// int	builtin_unset(t_parser *parser, t_env *env)
// {
	// env  = del_env(parser, env);
	// return (0);
// }



int	built_env(t_env *env)
{
	print_env_lst(env);
	return (0);
}

int	built_echo(t_parser *parser)
{
	int	flag;
	int	i;

	i = 1;
	flag = 1;
	if (ft_strncmp("-n" ,parser->cmd[i], 3) == 0) /// needs to replicate --n and -nnnnnnnnnn or -n -n -n 
	{
		flag = 0;
		i++;
	}
	while(parser->cmd[i])
	{
		if (!parser->cmd[i + 1])
			ft_putstr_fd(parser->cmd[i], STDOUT_FILENO);
		else
		{
			ft_putstr_fd(parser->cmd[i], STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
		}
		i++;
	}
	if (flag == 1)
		write(1, "\n", 1);
	return (0);
}

int	built_cd(t_parser *parser, t_env *env)
{	//need a filter to check if exists the env before cz might be unset and might need to be created.
	t_env	*iter;

	iter = env;
	while (iter->next && ft_strncmp(iter->name, "OLDPWD", 7) != 0)
		iter = iter->next;
	iter->content = ft_strdup(getcwd(NULL, MAXPATHLEN));
	iter = env;
	if (chdir(parser->cmd[1]) < 0)
		errno_printer(parser->cmd[0], strerror(errno), parser->cmd[1]);
	while (iter->next && ft_strncmp(iter->name, "PWD", 4) != 0)
		iter = iter->next;
	iter->content = ft_strdup(getcwd(NULL, MAXPATHLEN));
	return (0);
}

int	built_pwd()//(t_parser *parser)
{
	ft_printf("%s\n", getcwd(NULL, MAXPATHLEN));
	return (0);
}


int	is_builtin(t_parser *parser, t_env *env) 
{
	if (parser->cmd)//need to check til when we loop.
	{
		if (ft_strncmp("echo", parser->cmd[0], 5) == 0) 
		{
			if (!parser->cmd[1])
				return (write(1, "\n", 1));
			built_echo(parser);
		}
		else if (ft_strncmp("cd", parser->cmd[0], 3) == 0)
		{
			//check if pwd and old pwd exist;
			built_cd(parser, env);
		}
		else if (ft_strncmp("pwd", parser->cmd[0], 4) == 0)
			built_pwd();//(parser);
		else if (ft_strncmp("env", parser->cmd[0], 4) == 0)
			built_env(env);
		else if (ft_strncmp("exit", parser->cmd[0], 5) == 0)
			builtin_exit();
		// else if (ft_strncmp("export", parser->cmd[0], 7) == 0)
			// builtin_export(parser, env);
		// else if (ft_strncmp("unset", parser->cmd[0], 6) == 0)
			// builtin_unset(parser, env);
		// parser = parser->next;
	}
	return (0);
}

