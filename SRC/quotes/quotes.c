/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/06 19:37:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	s_has_q(char *str)
{
	int	i;
	i = 0;
	if (str)
	{
		while (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
			i++;
		if (str[i] == '\0')
			return (0);
		else if (str[i] == '\'')
			return (1);
		else if (str[i] == '\"')
			return (2);
	}
	return (0);
}

char *cnt_b_q(char *str, char c)
{
	int	i;
	char	*res;

	i = 0;
	if (str)
	{
		while (str[i] != c)
			i++;
		if (str[i] != c)
			return (NULL);
		i++;
		while (str[i] != c)
			i++;
		if (str[i] == c)
			res = malloc ((i + 1) * sizeof(char));
		i = -1;
		while (str[++i] != c)
			res[i] = str[i];
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}

char	*cnt_in_q(char *str, char c)
{
	int	i;
	int	j;
	char	*res;

	i = 0;
	while (str[i] != c)
		i++;
	i++;
	j = i;
	while (str[i] != c)
		i++;
	res = malloc (((i - j) + 1) *sizeof(char));
	i = 0;
	while (str[j] != c && str[j] != '\0')
	{
		res[i] = str[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*cnt_aft_q(char *str, char c)
{
	int	i;
	int j;
	char	*res;

	i = 0;
	while (str[i] != c)
		i++;
	i++;
	while (str[i] != c && str[i] != '\0')
		++i;
	if (str[i] == '\0' || str[++i] == '\0')
		return (NULL);
	j = i;
	while (str[i] != '\0')
		i++;
	res = malloc (((i - j) + 1) *sizeof(char));
	i = 0;
	while (str[j] != '\0')
	{
		res[i] = str[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

// lets try recursive solution so if tmp_after has content, calls again the clear quotes;

char	*clear_quotes(char *str, t_env *env, int exit_code, char *tmp_ex)
{
	char 	*tmp_bef;
	char	*tmp_cont;
	char	*tmp_after;
	char	*res;
	
	if (str)
		res = str;
	if (s_has_q(str) == 1)
	{
		tmp_bef = fnd_dllr(cnt_b_q(str, '\''), env, exit_code);
		tmp_cont = fnd_dllr(cnt_in_q(str, '\''), env, exit_code);
		tmp_after = fnd_dllr(cnt_aft_q(str, '\''), env, exit_code);
	}
	else if (s_has_q(str) == 2)
	{
		tmp_bef = cnt_b_q(str, '\"');
		tmp_cont = cnt_in_q(str, '\"');
		tmp_after = cnt_aft_q(str, '\"');
	}
	else 
		return (str);
}











/*
char	has_quotes(char *str)
{
	int	i;
	i = 0;
	if (!str)
	{
	//	ft_printf("fuck\n");
		return('\0');
	}
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
	//		ft_printf("%c\n", str[i]);
			return (str[i]);
		}
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
	if (c == '\0')
		return (NULL);//(ft_strdup(""));
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
		i++;
	if (str[i] == '\0')	
		return (NULL);
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	if (str[i] == '\0')
		return (NULL);
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
	
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != c)
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	if (str[i] == '\0')
		return (NULL);//when cont is empty
	j = i;
	while (str[i] != '\0' && str[i] != c)
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
	char *str;

	i = 0;
	if (!res)
		return (NULL);
	if (res[i] == c)
		return(NULL);
	if (res[i] != c && res[i] != '\0')
	{	
		while (res[i] != c && res[i] != '\0')
			i++;
		str = malloc ((i + 1) * sizeof(char));
		if (!str)
			return (NULL);
		i = 0;
		while (res[i] != c && res[i] != '\0')
		{
			str[i] = res[i];
			i++;
		}
		str[i] = '\0';
	}
	else
		return (NULL);	//(ft_strdup(""));
	return (str);
}


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
		tmp_bef = fnd_dllr(cont_bef_q(res, c), env, exit_code);
		if (c == '\"')
		{
			tmp_cont = cont_in_q(res, c);
			if (!tmp_cont)
				tmp_cont = NULL;
			tmp_ex = fnd_dllr(tmp_cont, env, exit_code);
			//free(tmp_cont);
			if (tmp_bef && tmp_ex)
			{
				tmp_cont = ft_strjoinplus(tmp_bef, tmp_ex);
				free(tmp_ex); //added at 09.41am, was commented before due it causin
			}
			else if (!tmp_ex)
				tmp_cont = tmp_bef;
			else if (!tmp_bef)
				tmp_cont = tmp_ex;
			else
				tmp_cont = ft_strdup("");
		}
		else if (c == '\'')
				tmp_cont = ft_strjoinplus(tmp_bef, cont_in_q(res, c));
		if (tmp_bef)
			free(tmp_bef);	//cause double free;
		tmp_after = cont_after_q(res, c);
		c = has_quotes(tmp_after);
		while (tmp_after && c != '\0')
		{
			tmp_bef = ft_strjoinplus(tmp_cont, fnd_dllr(cont_bef_q(tmp_after, c), env, exit_code));
			if (c == '\"')
				tmp_cont = ft_strjoinplus(tmp_bef, fnd_dllr(cont_in_q(tmp_after, c), env, exit_code));
			else if (c == '\'')
				tmp_cont = ft_strjoinplus(tmp_bef, cont_in_q(tmp_after, c));
			tmp_ex = cont_after_q(tmp_after, c);
			free(tmp_after);
			tmp_after = tmp_ex;
			c = has_quotes(tmp_after);
			free(tmp_bef);
		}
		res = ft_strjoinplus(tmp_cont, fnd_dllr(tmp_after, env, exit_code));
	}
	else
	{
		res = fnd_dllr(res, env, exit_code);
	}
	return (res);
}

*/