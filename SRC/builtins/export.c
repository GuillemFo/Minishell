/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:16:36 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/12 16:30:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_helper(t_parser *parser, int i, t_env **env, int *ret)
{
	int	x;

	x = 0;
	if ((is_poss_char(parser->cmd[i][0])) == 1)
	{
		while (is_poss_char(parser->cmd[i][x]) != 0)
			x++;
		if (parser->cmd[i][x] != '\0' && parser->cmd[i][x] != '=')
			*ret = errno_printer_2(parser->cmd[0],
					"not a valid identifier", parser->cmd[i], 1);
		else if (parser->cmd[i][x] == '\0' || parser->cmd[i][x] == '=')
			add_env(parser, env, i);
	}
	else
		*ret = errno_printer_2(parser->cmd[0],
				"not a valid identifier", parser->cmd[i], 1);
}

int	builtin_export(t_parser *parser, t_env **env, int ret)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	i = 1;
	if (!parser->cmd[1])
		print_hidden_lst(*env);
	while (parser->cmd[i])
	{
		tmp = get_til_equal(parser->cmd[i]);
		if (env_exist(*env, tmp) == false)
			builtin_helper(parser, i, env, &ret);
		else if (env_has_equal(parser->cmd[i]) == true)
			edit_env(parser, env, i, tmp2);
		i++;
		free(tmp);
	}
	return (ret);
}

void	set_null_hidden(t_env *iter)
{
	iter->content = NULL;
	iter->is_hidden = true;
}
