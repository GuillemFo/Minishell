/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:58:02 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/12 23:02:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*value_clear(char *s)
{
	int		i;
	char	*val;

	i = 0;
	if (s[i] == '0')
	{
		while (s[i] == '0')
			i++;
		val = ft_strdup(&s[i]);
	}
	else
		val = ft_strdup(s);
	return (val);
}

void	exit_support(t_parser *parser, int *error)
{
	char	*value;

	value = value_clear(parser->cmd[1]);
	if (ft_strlen(value) >= 19)
	{
		if (ft_strcmp("-9223372036854775808", value) == 0)
			*error = 0;
		else if (ft_strcmp("9223372036854775807", value) == 0)
			*error = 255;
		else
		{
			errno_printer(" exit",
				"numeric argument required", parser->cmd[1]);
			*error = 255;
		}
		free(value);
	}
	else
	{
		free(value);
		exit(ft_atoll(parser->cmd[1]));
	}
}

int	builtin_exit(t_parser *parser, int *error)
{
	if (parser->cmd[1] && ft_check_arg_is_num(parser->cmd[1]) != 1)
	{
		errno_printer(" exit", "numeric argument required", parser->cmd[1]);
		*error = 255;
	}
	else if (parser->cmd[1] && parser->cmd[2])
	{
		if (parser->cmd[1] && ft_check_arg_is_num(parser->cmd[2]) == 1)
		{
			ft_other_error("exit: too many arguments\n", error, 1);
			return (1);
		}
		else if (parser->cmd[1] && ft_check_arg_is_num(parser->cmd[2]) != 1)
		{
			ft_other_error("exit: too many arguments\n", error, 1);
			exit (1);
		}
	}
	else if (parser->cmd[1] && ft_check_arg_is_num(parser->cmd[1]) == 1)
		exit_support(parser, error);
	exit(*error);
}
