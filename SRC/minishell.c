/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:48:05 by codespace         #+#    #+#             */
/*   Updated: 2024/04/13 16:34:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*clean_input(t_parser *parser, t_env *env, int exit_code)
{
	int			i;
	t_parser	*itr;
	t_redir		*tmp;
	char		*tmp2;

	itr = parser;
	if (itr != NULL)
	{
		while (itr)
		{
			i = -1;
			while (itr->cmd && itr->cmd[++i] != NULL && itr->cmd[i][0] != '\0')
			{
				tmp2 = clear_quotes(&(itr->cmd[i]), env, exit_code);
				free(itr->cmd[i]);
				itr->cmd[i] = ft_strdup(tmp2);
				free(tmp2);
			}
			tmp = itr->redir;
			while (tmp && tmp->dest)
				cl_quotes_s(&tmp, &tmp2, env, exit_code);
			itr = itr->next;
		}
	}
	return (parser);
}

t_lexer	*function(int *error, char *str)
{
	*error = 0;
	return (ft_lexer(str));
}

char	*beginning(t_env **env, int *error, int *exit_code, char **envp)
{
	*env = inition_signals_env(error, exit_code, envp, *env);
	return (readline(C_G "minishell: " C_RESET));
}

int	main(int ac, char **av, char **envp)
{
	t_parser	*data;
	t_env		*env;
	t_errors	err;

	if (ac != 1)
		return (1);
	env = NULL;
	err.str = beginning(&env, &err.error, &err.exit_code, envp);
	if (err.str)
	{
		while (1)
		{
			my_add_history(err.str, av);
			if (err.str)
			{
				data = ft_parser(function(&err.error, err.str), &err.error);
				if (!err.error && data)
					executing(data, env, &err);
				err.str = freestyle(err.error, &err.exit_code, data, err.str);
				if (!err.str)
					break ;
			}
		}
	}
	return (returning(env, err.exit_code));
}
