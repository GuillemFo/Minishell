/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_support_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:17:14 by codespace         #+#    #+#             */
/*   Updated: 2024/04/13 13:46:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_q_6(t_tmp *tmp)
{
	tmp->tmp_ex = cnt_aft_q(tmp->tmp_after, tmp->c);
	free(tmp->tmp_after);
	tmp->tmp_after = tmp->tmp_ex;
}

void	clear_q_7(t_tmp *tmp, char **res, t_env *env, int exit_code)
{
	free(*res);
	tmp->tmp_ex = fnd_dllr(tmp->tmp_after, env, exit_code);
	*res = ft_strjoinplus(tmp->tmp_cont, tmp->tmp_ex);
	free(tmp->tmp_ex);
}

void	clear_q_8(t_tmp *tmp, char **res, t_env *env, int exit_code)
{
	tmp->tmp_ex = fnd_dllr(*res, env, exit_code);
	*res = tmp->tmp_ex;
}

void	multi_q(t_tmp *tmp, t_env *env, int exit_code)
{
	clear_q_3(tmp, env, exit_code);
	if (tmp->c == '\"')
		clear_q_4(tmp, env, exit_code);
	else if (tmp->c == '\'')
		clear_q_5(tmp);
	clear_q_6(tmp);
}
