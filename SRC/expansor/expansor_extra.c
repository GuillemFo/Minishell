/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 03:27:45 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/03 13:01:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str_extra(char *str, int exit_code)
{
	char	*cont;
	char	*tmp;
	char *tmp2;
	char	*result;

	cont = ft_itoa(exit_code);
	tmp2 = trim_bef(str, '$');
	tmp = ft_strjoini(tmp2, cont);
	free(tmp2);
	tmp2 = trim_after(str, '$');
	result = ft_strjoini(tmp, tmp2);
	free(cont);
	free(tmp);
	return (result);
}

char *find_dollar_var(char *str, int exit_code)
{
	int		x;
	char	*result;

	x = 0;
	result = str;
	while (result[x]!= '\0')
	{
		if (result[x] && result[x] == '$' && result[x + 1] == '?')
		{
			result = expand_str_extra(result, exit_code);
			x = -1;
		}
		x++;
	}
	return (result);
}
