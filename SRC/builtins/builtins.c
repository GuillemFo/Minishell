/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/03 08:17:52 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int		builtin_unset(t_parser *parser, t_env **env, int *error)
{
	int	i;

	i = 1;
	if (!parser->cmd[1])
		return (1);
	while (parser->cmd[i])
	{
		if (env_exist(*env, get_til_equal(parser->cmd[i])) == false)
		{
			*error = 1;
			return (*error);
		}
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

int	check_is_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		while (str[i] == '-' && str[i + 1] == 'n')
			i++;
		while (str[i] == 'n')
			i++;
		if	(str[i] == '\0')
			return (i);
		else
			return (0);
	}
	return (i);
}


int built_echo(t_parser *parser)
{
    int suppress_newline;
    int i;
	
	i = 1;
	suppress_newline = 0;
    while ((parser->cmd[i] != NULL && (check_is_n(parser->cmd[i]) != 0)))
	{
        if ((check_is_n(parser->cmd[i]) != 0))
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

t_env	**get_old_pwd(t_env **env)
{
	t_env *iter;

	iter = *env;
	while (iter->next && ft_strncmp(iter->name, "OLDPWD", 7) != 0)
		iter = iter->next;
	if (iter->name != NULL && ft_strncmp(iter->name, "OLDPWD", 7) == 0)
		{
			if (getcwd(NULL, MAXPATHLEN) != NULL)
				iter->content = getcwd(NULL, MAXPATHLEN);
			iter->is_hidden = false;
		}
	else if (!iter->next)
	{
		iter->next = malloc(sizeof(t_env));
		iter->next->name = ft_strdup("OLDPWD");
		if (getcwd(NULL, MAXPATHLEN) != NULL)
				iter->next->content = getcwd(NULL, MAXPATHLEN);
		iter->next->is_hidden = false;
		iter->next->next = NULL;
	}
	return(env);
}

t_env	**get_pwd(t_env **env)
{
	t_env *iter;

	iter = *env;
	while (iter->next && ft_strncmp(iter->name, "PWD", 4) != 0)
		iter = iter->next;
	if (iter->name != NULL && ft_strncmp(iter->name, "PWD", 4) == 0)
	{
		iter->content = getcwd(NULL, MAXPATHLEN);
		iter->is_hidden = false;
	}
	else if (!iter->next)
	{
		iter->next = malloc(sizeof(t_env));
		iter->next->name = ft_strdup("PWD");
		iter->next->content = getcwd(NULL, MAXPATHLEN);
		iter->next->is_hidden = false;
		iter->next->next = NULL;
	}
	return (env);
}

int	built_cd(t_parser *parser, t_env **env, int *error)
{
	char	*homedir;

	get_old_pwd(env);
	if (!parser->cmd[1])
	{
		homedir = get_home(*env);
		if (ft_strcmp(homedir, "ERROR") == 0)
			errno_printer(parser->cmd[0], "", "HOME not set");
		else if (chdir(homedir) < 0)
			errno_printer(parser->cmd[0], strerror(errno), homedir);
		*error = 0;
	}
	else if ((parser->cmd[1][0] != '\0') && (chdir(parser->cmd[1]) < 0))
	{
		errno_printer(parser->cmd[0], strerror(errno), parser->cmd[1]);
		*error = 1;
	}
	get_pwd(env);
	return (*error);
}

int	built_pwd()
{
	ft_printf("%s\n", getcwd(NULL, MAXPATHLEN));
	return (0);
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
		return(built_cd(parser, env, error));
	else if (ft_strcmp("pwd", parser->cmd[0]) == 0)
		return(built_pwd());
	else if (ft_strcmp("env", parser->cmd[0]) == 0)
		return(built_env(*env));
	else if (ft_strcmp("exit", parser->cmd[0]) == 0)
		return(builtin_exit(parser, error));
	else if (ft_strcmp("export", parser->cmd[0]) == 0)
		return(builtin_export(parser, env, error));
	else if (ft_strcmp("unset", parser->cmd[0]) == 0)
		return(builtin_unset(parser, env, error));
	return (0);
}
