/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:16:36 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/03 10:18:34 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_helper(t_parser *parser, int i, t_env **env, int *error)
{
	int x;
	x = 0;
	if ((is_poss_char(parser->cmd[i][0]))== 1)
	{
		while (is_poss_char(parser->cmd[i][x]) != 0)
			x++;
		if (parser->cmd[i][x] != '\0' && parser->cmd[i][x] != '=')
			*error = errno_printer_2(parser->cmd[0],
			"not a valid identifier", parser->cmd[i], 0);
		else if (parser->cmd[i][x] == '\0' || parser->cmd[i][x] == '=')
			add_env(parser, env, i);
	}
	else
		*error = errno_printer_2(parser->cmd[0],
		"not a valid identifier", parser->cmd[i], 0);
}


int		builtin_export(t_parser *parser, t_env **env, int *error)
{
	int	i;
	int	y;

	y = 0;
	i = 1;
	if (!parser->cmd[1])
		print_hidden_lst(*env);
	while (parser->cmd[i])
	{
		if (env_exist(*env, get_til_equal(parser->cmd[i])) == false)
			builtin_helper(parser, i, env, error);
		else if (equal_til_end(parser->cmd[i]))
			edit_env(parser, env, i);
		i++;
	}
	*error = y;
	return (y);
}



// int		builtin_export(t_parser *parser, t_env **env, int *error)
// {
// 	int	i;
// 	int	x;
// 	int	y;
// 
// 	y = 0;
// 	i = 1;
// 	if (!parser->cmd[1])
// 		print_hidden_lst(*env);
// 	while (parser->cmd[i])
// 	{
// 		if (env_exist(*env, get_til_equal(parser->cmd[i])) == false)
// 		{
// 			x = 0;
// 			if ((is_poss_char(parser->cmd[i][0]))== 1)
// 			{
// 				while (is_poss_char(parser->cmd[i][x]) != 0)
// 					x++;
// 				if (parser->cmd[i][x] != '\0' && parser->cmd[i][x] != '=')
// 					*error = errno_printer_2(parser->cmd[0],
// 					"not a valid identifier", parser->cmd[i], 0);
// 				else if (parser->cmd[i][x] == '\0' || parser->cmd[i][x] == '=')
// 					add_env(parser, env, i);
// 			}
// 			else
// 				*error = errno_printer_2(parser->cmd[0],
// 				"not a valid identifier", parser->cmd[i], 0);
// 		}
// 		else if (equal_til_end(parser->cmd[i]))
// 				edit_env(parser, env, i);
// 		i++;
// 	}
// 	*error = y;
// 	return (y);
// }
// 