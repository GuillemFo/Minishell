/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:10:21 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/05 09:46:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int		builtin_unset(t_parser *parser, t_env **env)
{
	int	i;
	char *tmp;

	i = 1;
	if (!parser->cmd[1])
		return (0);
	while (parser->cmd[i])
	{
		tmp = get_til_equal(parser->cmd[i]);
		// if (env_exist(*env, tmp) == false)
		// else if (env_exist(*env, tmp) == true)
		// 	del_env(parser, env, i);
		if (env_exist(*env, tmp) == true)
			del_env(parser, env, i);
		free(tmp);
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
	char	*tmp;

	tmp = getcwd(NULL, MAXPATHLEN);
	iter = *env;
	while (iter->next && ft_strncmp(iter->name, "OLDPWD", 7) != 0)
		iter = iter->next;
	if (iter->name != NULL && ft_strncmp(iter->name, "OLDPWD", 7) == 0)
		{
			if (tmp != NULL)
			{
				free (iter->content);
				iter->content = tmp;
				iter->is_hidden = false;
			} 
		}
	else if (!iter->next && tmp)
	{
		iter->next = malloc(sizeof(t_env));
		iter->next->name = ft_strdup("OLDPWD");
		iter->next->content = tmp;
		iter->next->is_hidden = false;
		iter->next->next = NULL;
	}
	return(env);
}

t_env	**get_pwd(t_env **env)
{
	t_env *iter;
	char	*tmp;

	tmp = getcwd(NULL, MAXPATHLEN);
	iter = *env;
	while (iter->next && ft_strncmp(iter->name, "PWD", 4) != 0)
		iter = iter->next;
	if (iter->name != NULL && ft_strncmp(iter->name, "PWD", 4) == 0)
	{
		free (iter->content);
		iter->content = tmp;
		iter->is_hidden = false;
	}
	else if (!iter->next && tmp)
	{
		iter->next = malloc(sizeof(t_env));
		iter->next->name = ft_strdup("PWD");
		iter->next->content = tmp;
		iter->next->is_hidden = false;
		iter->next->next = NULL;
	}
	return (env);
}

int	built_cd(t_parser *parser, t_env **env, int ret)
{
	char	*homedir;

	ret = 0;
	get_old_pwd(env);
	if (!parser->cmd[1])
	{
		homedir = get_home(*env);
		if (!homedir)
		{
			errno_printer_home(parser->cmd[0], "HOME not set");
			ret = 1;
		}
		else if (chdir(homedir) < 0)
		{
			errno_printer(parser->cmd[0], strerror(errno), homedir);
			ret = 1;
		}
	}
	else if ((parser->cmd[1][0] != '\0') && (chdir(parser->cmd[1]) < 0))
	{
		errno_printer(parser->cmd[0], strerror(errno), parser->cmd[1]);
		ret = 1;
	}
	get_pwd(env);	//check if it changes correctly or i need to equal to env;
	return (ret);
}

int	built_pwd()
{
	char	*tmp;

	tmp = getcwd(NULL, MAXPATHLEN);
	ft_printf("%s\n", tmp);
	free (tmp);
	return (0);
}

int	is_builtin_execute(t_parser *parser, t_env **env, int *error) 
{
	int	ret;

	ret = 0;
	if (ft_strcmp("echo", parser->cmd[0]) == 0)
	{
		if (!parser->cmd[1])
			return (ft_printf("\n"), 0);
		return(built_echo(parser));
	}
	else if (ft_strcmp("cd", parser->cmd[0]) == 0)
		return(built_cd(parser, env, ret));
	else if (ft_strcmp("pwd", parser->cmd[0]) == 0)
		return(built_pwd());
	else if (ft_strcmp("env", parser->cmd[0]) == 0)
		return(built_env(*env));
	else if (ft_strcmp("exit", parser->cmd[0]) == 0)
		return(builtin_exit(parser, error));
	else if (ft_strcmp("export", parser->cmd[0]) == 0)
		return(builtin_export(parser, env, ret));
	else if (ft_strcmp("unset", parser->cmd[0]) == 0)
		return(builtin_unset(parser, env));
	return (0);
}
