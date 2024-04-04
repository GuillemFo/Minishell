/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/04 09:42:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	has_quotes(char *str)
{
	int	i;
	i = 0;
	if (!str)
	{
		ft_printf("fuck\n");
		return('\0');
	}
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			ft_printf("%c\n", str[i]);
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
		return (ft_strdup(""));
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
	
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != c)
		i++;
	i++;
	if (str[i] == '\0')
		return (ft_strdup(""));//when cont is empty
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
		return (ft_strdup(""));
	return (str);
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
		tmp_bef = find_dollar(cont_bef_q(res, c), env, exit_code);//no leaks
		if (c == '\"')
		{
			tmp_ex = find_dollar(cont_in_q(res, c), env, exit_code);
			ft_printf("%s\n", tmp_ex);
			tmp_cont = ft_strjoinplus(tmp_bef, tmp_ex);		//leaks here always
			free(tmp_ex);
		}
		else if (c == '\'')
		{
			tmp_ex = cont_in_q(res, c);
			tmp_cont = ft_strjoinplus(tmp_bef, tmp_ex);
			free(tmp_ex);
		}
		else
			tmp_cont = tmp_bef;
		tmp_after = cont_after_q(res, c);
		c = has_quotes(tmp_after);
		while (c != '\0' && tmp_after)
		{
			tmp_ex = find_dollar(cont_bef_q(tmp_after, c),env, exit_code);
			tmp_bef = ft_strjoinplus(tmp_cont, tmp_ex);
			free(tmp_ex);
			if (c == '\"')
			{
				tmp_ex = find_dollar(cont_in_q(tmp_after, c), env, exit_code);
				tmp_cont = ft_strjoinplus(tmp_bef, tmp_ex);
				free(tmp_ex);
			}
			else if (c == '\'')
			{
				tmp_ex = cont_in_q(tmp_after, c);
				tmp_cont = ft_strjoinplus(tmp_bef, tmp_ex);
				free(tmp_ex);
			}
			tmp_ex = cont_after_q(tmp_after, c);
			free(tmp_after);
			tmp_after = tmp_ex;
			c = has_quotes(tmp_after);
			free(tmp_bef);
		}
		res = ft_strjoinplus(tmp_cont, find_dollar(tmp_after, env, exit_code));
	}
	else
	{
		res = find_dollar(res, env, exit_code);
	}
	return (res);
}



// char	*clear_quotes(char *str, t_env *env, int exit_code, char *tmp_ex)
// {
// 	char 	*tmp_bef;
// 	char	*tmp_cont;
// 	char	*tmp_after;
// 	char	*res;
// 	char	c;
// 	
// 	if (str)
// 		res = str;
// 	else
// 		return (NULL);
// 	c = has_quotes(res);
// 	if (c != '\0')
// 	{
// 		tmp_bef = find_dollar(cont_bef_q(res, c), env, exit_code);
// 		if (c == '\"')
// 		{
// 			tmp_cont = cont_in_q(res, c);
// 			tmp_ex = find_dollar(tmp_cont, env, exit_code);
// 			//free(tmp_cont);
// 			tmp_cont = ft_strjoinplus(tmp_bef, tmp_ex);
// 			free(tmp_ex); //added at 09.41am, was commented before due it causin
// 		}
// 		else if (c == '\'')
// 				tmp_cont = ft_strjoinplus(tmp_bef, cont_in_q(res, c));
// 		if (tmp_bef)
// 			free(tmp_bef);	//cause double free;
// 		ft_printf("filter:%c:\n", c);
// 		tmp_after = cont_after_q(res, c);
// 		c = has_quotes(tmp_after);
// 		if (!tmp_after)
// 			return (ft_printf("here is the issue\n"), NULL);
// 		while (c != '\0')
// 		{
// 			tmp_bef = ft_strjoinplus(tmp_cont, find_dollar(cont_bef_q(tmp_after,
// 			if (c == '\"')
// 				tmp_cont = ft_strjoinplus(tmp_bef, find_dollar(cont_in_q(tmp_aft
// 			else if (c == '\'')
// 				tmp_cont = ft_strjoinplus(tmp_bef, cont_in_q(tmp_after, c));
// 			tmp_ex = cont_after_q(tmp_after, c);
// 			free(tmp_after);
// 			tmp_after = tmp_ex;
// 			c = has_quotes(tmp_after);
// 			free(tmp_bef);
// 		}
// 		res = ft_strjoinplus(tmp_cont, find_dollar(tmp_after, env, exit_code));
// 	}
// 	else
// 	{
// 		res = find_dollar(res, env, exit_code);
// 	}
// 	return (res);
// }
