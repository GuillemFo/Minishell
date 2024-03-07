/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/07 14:01:58 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//This has to return the proper value
int	builtin_exit(t_parser *parser)
{
	int	val;
	if (!parser->cmd[1])
		exit(0);
	else if (parser->cmd[1])
	{
		if (check_is_all_numbers(parser->cmd[1]) == 1)	//Need to build this function
		{
			val = ft_atoi(parser->cmd[1]);
			if (val < 0 || val > 255)
			{
				errno_printer("exit", "numeric argument required", parser->cmd[1]);
				exit(0);
			}
			else if (val >= 0 && val <= 255)
				exit(val);
		}
	}
		exit(255);
	return (0);
}


//if we have multiple args, will set all. Some characters are not valid!!
//check if has equial in order to actually rewrite it empty;
int		builtin_export(t_parser *parser, t_env *env)
{
	if (!parser->cmd[1])
		print_hidden_lst(env);
	else if (env_exist(env, get_til_equal(parser->cmd[1])) == false)
		env = add_env(parser, env);
	else
		env = edit_env(parser, env);							
	return (0);
}



//check if characters are valid.
//will not do anything if does not exists;
int	builtin_unset(t_parser *parser, t_env *env)
{
	if (env_exist(env, get_til_equal(parser->cmd[1])) == false)
		return (0);
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
	if (ft_strncmp("-n" ,parser->cmd[i], 3) == 0) /// needs to replicate -nnnnnnnnnn or -n -n -n 
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

//need a filter to check if exists the env before cz might be unset and might need to be created.
int	built_cd(t_parser *parser, t_env *env)
{
	t_env	*iter;
	char	*homedir;

	iter = env;
	while (iter->next && ft_strncmp(iter->name, "OLDPWD", 7) != 0)
		iter = iter->next;
	iter->content = ft_strdup(getcwd(NULL, MAXPATHLEN));
	iter = env;
	if (!parser->cmd[1])
	{
		homedir = get_home(env);
		if (ft_strcmp(homedir, "ERROR") == 0)
			errno_printer(parser->cmd[0], strerror(errno), "HOME not set\n");
		if (chdir(homedir) < 0)
			errno_printer(parser->cmd[0], strerror(errno), "homedir\n");
	}
	else if (chdir(parser->cmd[1]) < 0)
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


int	is_builtin_execute(t_parser *parser, t_env *env) 
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
		return(builtin_exit(parser));
	else if (ft_strncmp("export", parser->cmd[0], 7) == 0)
		return(builtin_export(parser, env));
	else if (ft_strncmp("unset", parser->cmd[0], 6) == 0)
		return(builtin_unset(parser, env));
	return (0);
}



