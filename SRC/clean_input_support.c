/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input_support.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:58:34 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/13 14:23:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cl_quotes_s(t_redir **tmp, char **tmp2, t_env *env, int exit_code)
{
	*tmp2 = clear_quotes(&(*tmp)->dest, env, exit_code);
	free((*tmp)->dest);
	(*tmp)->dest = *tmp2;
	*tmp = (*tmp)->next;
}
