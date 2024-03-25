/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/25 19:09:02 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*value_clear(char *s)
{
	int i;
	char *val;

	i = 0;
	if (s[i] == '0')
	{
		while (s[i] == '0')
			i++;
		val = ft_strdup(&s[i]);
	}
	else
		val = ft_strdup(s);
	return	(val);
}

//	!!! Reminder that exit will round values every 255 reached !!!
//	and val cant exceed __LONG_LONG_MAX__
int	builtin_exit(t_parser *parser, int *error)
{
	char *value;
	if (parser->cmd[1] && parser->cmd[2])
	{
		ft_other_error("exit: too many arguments\n", error, 1);
		return (1);
	}
	else if (parser->cmd[1] && ft_check_arg_is_num(parser->cmd[1]) != 1) // atoi checker
	{
		errno_printer(" exit", "numeric argument required", parser->cmd[1]);
		*error = 255;
	}
	else if (parser->cmd[1] && ft_check_arg_is_num(parser->cmd[1]) == 1)
	{
		value = value_clear(parser->cmd[1]);
		if (ft_strlen(value) >=19)
		{
			if (ft_strcmp("-9223372036854775808", value) == 0)
				*error = 0;
			else if (ft_strcmp("9223372036854775807", value) == 0)
				*error = 255;
			else
			{
				errno_printer(" exit", "numeric argument required", parser->cmd[1]);
				*error = 255;
			}
		}
		else
			exit(ft_atoi(parser->cmd[1]));
	}
	exit(*error);
}


//if we have multiple args, will set all. Some characters are not valid!!
//check if has equial in order to actually rewrite it empty;
int		builtin_export(t_parser *parser, t_env **env)
{
	int	i;
	int	x;
	int	y;

	y = 0;
	i = 1;
	if (!parser->cmd[1])
		print_hidden_lst(*env);
	while (parser->cmd[i])
	{
		if (env_exist(*env, get_til_equal(parser->cmd[i])) == false)
		{
			x = 0;
			if ((is_poss_char(parser->cmd[i][0]))== 1)
			{
				while (is_poss_char(parser->cmd[i][x]) != 0)
					x++;
				if (parser->cmd[i][x] != '\0' && parser->cmd[i][x] != '=')
					y = errno_printer_2(parser->cmd[0], "not a valid identifier", parser->cmd[i], 1);
				else if (parser->cmd[i][x] == '\0' || parser->cmd[i][x] == '=')
					add_env(parser, env, i);
			}
			else
				y = errno_printer_2(parser->cmd[0], "not a valid identifier", parser->cmd[i], 1);
		}
		else if (equal_til_end(parser->cmd[i]))
				edit_env(parser, env, i);
		i++;
	}						
	return (y);
}

int	builtin_unset(t_parser *parser, t_env **env)
{
	int	i;

	i = 1;
	if (!parser->cmd[1])
		return (1);
	while (parser->cmd[i])
	{
		if (env_exist(*env, get_til_equal(parser->cmd[i])) == false)
			return (1);
		else if (env_exist(*env, get_til_equal(parser->cmd[i])) == true)
			del_env(parser, env, i);
		i++;
	}
	return (0);
}



int	built_env(t_env *env)
{
	print_env_lst(env);
	return (0);
}

int built_echo(t_parser *parser)
{
    int suppress_newline;
    int i;
	i = 1;
	suppress_newline = 0;

    while ((parser->cmd[i] != NULL && ((ft_strcmp("-n", parser->cmd[i]) == 0) || ft_strcmp("-nn", parser->cmd[i]) == 0)))
	{
        if (ft_strncmp("-n", parser->cmd[i], 2) == 0)
            suppress_newline = 1;
        i++;
    }

    while (parser->cmd[i] != NULL)
	{
        ft_putstr_fd(parser->cmd[i], STDOUT_FILENO);
        if (parser->cmd[i + 1] != NULL)
            write(1, " ", 1);
        i++;
    }

    if (!suppress_newline)
        write(1, "\n", 1);

    return (0);
}

//need a filter to check if exists the env before cz might be unset and might need to be created.
int	built_cd(t_parser *parser, t_env **env)
{
	t_env	*iter;
	char	*homedir;

	iter = *env;
	while (iter->next && ft_strncmp(iter->name, "OLDPWD", 7) != 0)
		iter = iter->next;
	if (iter->name != NULL && ft_strncmp(iter->name, "OLDPWD", 7) == 0)
		{
			iter->content = ft_strdup(getcwd(NULL, MAXPATHLEN));
			iter->is_hidden = false;
		}
	else if (!iter->next)
	{
		iter->next = malloc(sizeof(t_env));
		iter->next->name = ft_strdup("OLDPWD");
		iter->next->content = ft_strdup(getcwd(NULL, MAXPATHLEN));
		iter->next->is_hidden = false;
		iter->next->next = NULL;
	}
	if (ft_strncmp(iter->name, "PWD", 7) != 0)
	{
		iter = *env;
		while (iter->next && ft_strncmp(iter->name, "PWD", 4) != 0)
			iter = iter->next;
		if (iter->name != NULL && ft_strncmp(iter->name, "PWD", 4) == 0)
		{
			iter->content = ft_strdup(getcwd(NULL, MAXPATHLEN));
			iter->is_hidden = false;
		}
		else if (!iter->next)
		{
			iter->next = malloc(sizeof(t_env));
			iter->next->name = ft_strdup("PWD");
			iter->next->content = ft_strdup(getcwd(NULL, MAXPATHLEN));
			iter->next->is_hidden = false;
			iter->next->next = NULL;
		}
	}
	iter = *env;
	if (!parser->cmd[1])
	{
		homedir = get_home(*env);
		if (ft_strcmp(homedir, "ERROR") == 0)
			errno_printer(parser->cmd[0], "", "HOME not set");
		else if (chdir(homedir) < 0)
			errno_printer(parser->cmd[0], strerror(errno), homedir);
		return (1);
	}
	else if ((parser->cmd[1][0] != '\0') && (chdir(parser->cmd[1]) < 0))
	{
		errno_printer(parser->cmd[0], strerror(errno), parser->cmd[1]);
		return (1);
	}
	return (0);
}

int	built_pwd()
{
	ft_printf("%s\n", getcwd(NULL, MAXPATHLEN));
	return (1);
}


int	is_builtin_execute(t_parser *parser, t_env **env, int *error) 
{
	if (ft_strcmp("echo", parser->cmd[0]) == 0)
	{
		if (!parser->cmd[1])
			return (write(1, "\n", 1));
		return(built_echo(parser));
	}
	else if (ft_strcmp("cd", parser->cmd[0]) == 0)
		return(built_cd(parser, env));
	else if (ft_strcmp("pwd", parser->cmd[0]) == 0)
		return(built_pwd());
	else if (ft_strcmp("env", parser->cmd[0]) == 0)
		return(built_env(*env));
	else if (ft_strcmp("exit", parser->cmd[0]) == 0)
		return(builtin_exit(parser, error));
	else if (ft_strcmp("export", parser->cmd[0]) == 0)
		return(builtin_export(parser, env));
	else if (ft_strcmp("unset", parser->cmd[0]) == 0)
		return(builtin_unset(parser, env));
	return (0);
}
