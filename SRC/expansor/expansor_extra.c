/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 03:27:45 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/26 03:35:57 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str_extra(char *str, int exit_code)
{
	char	*cont;
	char	*tmp;
	char	*result;

	cont = ft_itoa(exit_code);
	tmp = ft_strjoini(trim_bef(str, '$'), cont);
	result = ft_strjoini(tmp, trim_after(str, '$'));
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