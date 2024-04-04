/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/04 05:06:52 by codespace        ###   ########.fr       */
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
	if (!str)
		return (NULL);
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
	res = ft_strncpy(res, &str[i], len);
	return (res);
}

char	*cont_in_q(char *str, char c)
{
	int i;
	int	j;
	char *cont;
	
	if (!str)
		return (NULL);
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

char *cont_bef_q(char *res, char c) /// A CHUPARLA 
{
	int i;
	char *text;

	i = 0;
	if (res[i] != c && res[i] != '\0')
	{	
		while (res[i] != c && res[i] != '\0')
			i++;
		text = malloc ((i + 1) * sizeof(char));
		if (!text)
			return (NULL);
		i = 0;
		while (res[i] != c && res[i] != '\0')
		{
			text[i] = res[i];
			i++;
		}
		text[i] = '\0';
	}
	else
		return (NULL);
	return (text);
}


// Leaks here!!
char	*clear_quotes(char *str, t_env *env, int exit_code, char *tmp_ex)
{
	char 	*tmp_bef;
	char	*tmp_cont;
	char	*tmp_after;
	char	*res;
	char	c;
	
	if (str)
		res = str;
	else
		return (NULL);
	c = has_quotes(res);
	if (c != '\0')
	{
		tmp_bef = find_dollar(cont_bef_q(res, c), env, exit_code);
		if (c == '\"')
		{
			tmp_ex = cont_in_q(res, c);
			tmp_cont = ft_strjoinplus(tmp_bef, find_dollar(tmp_ex, env, exit_code));
			//free(tmp_ex); if i add this free its a double free, but if its not then its leak.
		}
		else if (c == '\'')
				tmp_cont = ft_strjoinplus(tmp_bef, cont_in_q(res, c));
		free(tmp_bef);
		tmp_after = cont_after_q(res, c);
		while ((c = has_quotes(tmp_after)) != '\0')
		{
			tmp_bef = ft_strjoinplus(tmp_cont, find_dollar(cont_bef_q(tmp_after, c),env, exit_code));
			if (c == '\"')
				tmp_cont = ft_strjoinplus(tmp_bef, find_dollar(cont_in_q(tmp_after, c), env, exit_code));
			else if (c == '\'')
				tmp_cont = ft_strjoinplus(tmp_bef, cont_in_q(tmp_after, c));
			tmp_ex = cont_after_q(tmp_after, c);
			free(tmp_after);
			tmp_after = tmp_ex;
			free(tmp_bef);
		}
		free(res);
		res = ft_strjoinplus(tmp_cont, find_dollar(tmp_after, env, exit_code));
		if (tmp_cont)
			free(tmp_cont);
	}
	else
	{
		res = find_dollar(res, env, exit_code);
	}
	return (res);
}
