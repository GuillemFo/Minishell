/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/25 09:58:34 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	has_quotes(char *str)
{
	int	i;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (str[i]);
		i++;
	}
	return ('\0');
}

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
	int	j;
	char *cont;
	
	i = 0;
	while (str[i] != c)
		i++;
	i++;
	j = i;
	while (str[i] != c && str[i] != '\0')
		i++;
	cont = malloc((i - j + 1) * sizeof(char));
	if (!cont)
		return (NULL);
	i = j;
	j = 0;
	while (str[i] != c && str[i] != '\0')
	{
		cont[j] = str[i];
		i++;
		j++;
	}
	cont[j] = '\0';
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
		if (!res)
			return (NULL);
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

char	*clear_quotes(char *str, t_env *env, int exit_code)
{
	char 	*tmp_bef;
	char	*tmp_cont;
	char	*tmp_after;
	char	*res;
	char	c;
	//printf("%p\n", str);
	res = ft_strdup(str);
	c = has_quotes(res);
	if (c != '\0')
	{
		tmp_bef = find_dollar(cont_bef_q(res, c), env, exit_code);
		if (c == '\"')
			tmp_cont = ft_strjoini(tmp_bef, find_dollar(cont_in_q(res, c), env, exit_code));
		else if (c == '\'')
				tmp_cont = ft_strjoini(tmp_bef, cont_in_q(res, c));
		tmp_after = cont_after_q(res, c);
		while ((c = has_quotes(tmp_after)) != '\0') // do the tmp_bef and tmp_cont and add it to old tmp_cont?? so it wont redo the other string and clean possible ' or " might encounter?
		{
			tmp_bef = ft_strjoini(tmp_cont, find_dollar(cont_bef_q(tmp_after, c),env, exit_code));
			if (c == '\"')
				tmp_cont = ft_strjoini(tmp_bef, find_dollar(cont_in_q(tmp_after, c), env, exit_code));
			else if (c == '\'')
				tmp_cont = ft_strjoini(tmp_bef, cont_in_q(tmp_after, c));
			tmp_after = cont_after_q(tmp_after, c);
		}
		
		res = ft_strjoini(tmp_cont, find_dollar(tmp_after, env, exit_code));
	}
	else
		res = find_dollar(res, env, exit_code);
	return (res);
}




















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
