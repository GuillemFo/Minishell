/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 03:27:45 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/12 22:13:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str_extra(char *str, int exit_code, int *x)
{
	char	*cont;
	char	*tmp;
	char	*tmp2;
	char	*result;

	*x = -1;
	cont = ft_itoa(exit_code);
	tmp2 = trim_bef(str, '$');
	tmp = ft_strjoinplus(tmp2, cont);
	tmp2 = trim_after(str, '$');
	result = ft_strjoinplus(tmp, tmp2);
	free(cont);
	free(tmp2);
	free(str);
	return (result);
}

char	*fnd_dllr_var(char *str, int exit_code)
{
	int		x;
	char	*result;

	x = 0;
	result = str;
	while (result[x] != '\0')
	{
		if (result[x] && result[x] == '$' && result[x + 1] == '?')
			result = expand_str_extra(result, exit_code, &x);
		x++;
	}
	return (result);
}
