/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/06 09:53:47 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_exit()
{
	return (0);
}



int		builtin_export(t_parser *parser, t_env *env)
{
	if (!parser->cmd[1])
		print_hidden_lst(env);
	//check if characters are valid.
	else if (env_exist(env, get_til_equal(parser->cmd[1])) == false)	//if we have multiple args, will set all. Some characters are not valid!!
		env = add_env(parser, env);			//pending to check :)
	else
	env = edit_env(parser, env);							
	return (0);
}



int	builtin_unset(t_parser *parser, t_env *env)
{
	//check if characters are valid.
	if (env_exist(env, get_til_equal(parser->cmd[1])) == false)
		return (0);//will not do anything if does not exists;
	else if (env_exist(env, get_til_equal(parser->cmd[1])) == true)
	env  = del_env(parser, env);
	return (1);
}



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
	if (ft_strncmp("echo", parser->cmd[0], 5) == 0) 
	{
		if (!parser->cmd[1])
			return (write(1, "\n", 1));
		return(built_echo(parser));
	}
	else if (ft_strncmp("cd", parser->cmd[0], 3) == 0)
	{
		//check if pwd and old pwd exist;
		return(built_cd(parser, env));
	}
	else if (ft_strncmp("pwd", parser->cmd[0], 4) == 0)
		return(built_pwd());//(parser);
	else if (ft_strncmp("env", parser->cmd[0], 4) == 0)
		return(built_env(env));
	else if (ft_strncmp("exit", parser->cmd[0], 5) == 0)
		return(builtin_exit());
	else if (ft_strncmp("export", parser->cmd[0], 7) == 0)
		return(builtin_export(parser, env));
	else if (ft_strncmp("unset", parser->cmd[0], 6) == 0)
		return(builtin_unset(parser, env));
	return (1);
}

