/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:13:07 by codespace         #+#    #+#             */
/*   Updated: 2024/04/13 13:46:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_q_1(t_tmp *tmp, char **res, t_env *env, int exit_code)
{
	tmp->tmp_ex = cnt_in_q(*res, tmp->c);
	tmp->tmp_help = fnd_dllr(tmp->tmp_ex, env, exit_code);
	tmp->tmp_cont = ft_strjoinplus(tmp->tmp_bef, tmp->tmp_help);
	free(tmp->tmp_help);
}

void	clear_q_2(t_tmp *tmp, char **res)
{
	tmp->tmp_ex = cnt_in_q(*res, tmp->c);
	tmp->tmp_cont = ft_strjoinplus(tmp->tmp_bef, tmp->tmp_ex);
	free(tmp->tmp_ex);
	tmp->tmp_bef = NULL;
}

void	clear_q_3(t_tmp *tmp, t_env *env, int exit_code)
{
	tmp->c = has_quotes(tmp->tmp_after);
	tmp->tmp_ex = cnt_b_q(tmp->tmp_after, tmp->c);
	tmp->tmp_help = fnd_dllr(tmp->tmp_ex, env, exit_code);
	tmp->tmp_bef = ft_strjoinplus(tmp->tmp_cont, tmp->tmp_help);
	free(tmp->tmp_help);
}

void	clear_q_4(t_tmp *tmp, t_env *env, int exit_code)
{
	tmp->tmp_ex = cnt_in_q(tmp->tmp_after, tmp->c);
	tmp->tmp_help = fnd_dllr(tmp->tmp_ex, env, exit_code);
	tmp->tmp_cont = ft_strjoinplus(tmp->tmp_bef, tmp->tmp_help);
	free(tmp->tmp_help);
}

void	clear_q_5(t_tmp *tmp)
{
	tmp->tmp_ex = cnt_in_q(tmp->tmp_after, tmp->c);
	tmp->tmp_cont = ft_strjoinplus(tmp->tmp_bef, tmp->tmp_ex);
	free(tmp->tmp_ex);
}
