/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/20 11:10:08 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cont_after_q(char *str, char c)
{
	int i;
	int	len;
	char *res;
	
	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
		i++;
	len = ft_strlen(&str[i]);
	res = malloc((len + 1) * sizeof(char));
	ft_strncpy(res, &str[i], len);
	return (res);
}

char	*cont_in_q(char *str, char c)
{
	int i;
	char *cont;
	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
	{
		cont = malloc((i+1) * sizeof(char));
		i = -1;
		while (str[++i] != c && str[i] != '\0')
			cont[i] = str[i];
		cont[i] = '\0';
	}
	else
		cont = ft_strdup("error"); //perror and call readline again?
	return (cont);
}

char *cont_bef_q(char *str, char c)
{
	int i;
	char *res;
	
	i = 0;
	res = ft_strdup(str);
	if (str[i] != c && str[i] != '\0')
	{	
		while (str[i] != c && str[i] != '\0')
			i++;
		res = malloc ((i + 1) * sizeof(char));
		i = 0;
		while (str[i] != c && str[i] != '\0')
		{
			res[i] = str[i];
			i++;
		}
		res[i] = '\0';
	}
	else
		res = ft_strdup("");
	return (res);
}

char	*quotes_pain(char *str)
{
	char *tmp_bef;
	char	*tmp_cont;
	char *res;
	int	i;

	res = ft_strdup(str);
	i = 0;
	while (res[i] != '\0')
	{
		if (res[i] == '\"' && res[i + 1] != '\0')
		{
			++i;
			tmp_bef = cont_bef_q(res, '\"');
			tmp_cont = ft_strjoin(tmp_bef, cont_in_q(&res[i], '\"'));
			res = ft_strjoin(tmp_cont, cont_after_q(res, '\"'));
			i = 0;
		}
		i++;
	}
	return (res);
}
