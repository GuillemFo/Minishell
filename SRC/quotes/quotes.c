/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/28 09:34:23 by gforns-s         ###   ########.fr       */
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
		cont = malloc((i+1) * sizeof(char));
		i = -1;
		while (str[++i] != c && str[i] != '\0')
			cont[i] = str[i];
		cont[i] = '\0';
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

char	*clear_quotes(char *str)
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
		else if (res[i] == '\'' && res[i + 1] != '\0')
		{
			++i;
			tmp_bef = cont_bef_q(res, '\'');
			tmp_cont = ft_strjoin(tmp_bef, cont_in_q(&res[i], '\''));
			res = ft_strjoin(tmp_cont, cont_after_q(res, '\''));
			i = 0;
		}
		i++;
	}
	return (res);
}


// 28/02 09.34 --> stressed af. 
// Back again restructuring quotes. I need to trim before and after but not redo the content i already worked with.
// Need to find a way to work with before quotes and quotes content but when clearing again the data i work only with the after data.
// Maybe 

























// char	has_quotes(char *str)
// {
// 	int	i;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"' || str[i] == '\'')
// 			return (str[i]);
// 		i++;
// 	}
// 	return (str[i]);
// }

// char	*clear_quotes(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	c;
// 	char 	*cpy;
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*tmp3;
// 	char	*tmp4;

// 	i = 0;
// 	cpy = ft_strdup(str);
// 	c = has_quotes(cpy);
	
// 	if (c != '\0')
// 	{
// 		while (cpy[i] != c)
// 			i++;
// 		tmp = malloc(i + 1 *sizeof(char));
// 		i = 0;
// 		while (cpy[i] != c)
// 		{
// 			tmp[i] = cpy[i];
// 			i++;
// 		}
// 		tmp[i] = '\0';
// 		i++;
// 		j = i;
// 		while (cpy[i] != c && cpy[i] != '\0')
// 			i++;
// 		tmp2 = malloc((i - j + 1) *sizeof(char));
// 		i = j;
// 		j = 0;
// 		while (cpy[i] != c && cpy[i] != '\0')
// 		{
// 			tmp2[j] = cpy[i];
// 			i++;
// 			j++;
// 		}
// 		tmp2[j] = '\0';
// 		if (cpy[i] == '\0')
// 		{
// 			free(cpy);
// 			cpy = ft_strjoinplus(tmp, tmp2);
// 			return (cpy);
// 		}
// 		i++;
// 		j = i;
// 		while (cpy[i] != '\0')
// 			i++;
// 		tmp3 = malloc((i - j + 1) * sizeof(char));
// 		i = j;
// 		j = 0;
// 		while (cpy[i] != '\0')
// 		{
// 			tmp3[j] = cpy[i];
// 			i++;
// 			j++;
// 		}
// 		tmp3[j] = '\0';
// 		tmp4 = ft_strjoinplus(tmp, tmp2);
// 		cpy = ft_strjoinplus(tmp4, tmp3);
// 	}
// 	else
// 		return (cpy);
// 	return (str);
// }
