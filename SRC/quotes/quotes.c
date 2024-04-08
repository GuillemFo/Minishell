/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/08 10:55:29 by codespace        ###   ########.fr       */
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
		if (str[i] != '\0')
			res = malloc ((i + 1) * sizeof(char));
		i = 0;
		while (str[i] != c && str[i] != '\0')
		{
			res[i] = str[i];
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}

//	ft_printf("cont in q:%c:\n", str[i]);

char	*cnt_in_q(char *str, char c)
{
	int	i;
	int	j;
	char	*res;

	i = 0;
	while (str[i] != c)
		i++;
	i++;
	if (str[i] == '\0')
		return (NULL);
	j = i;
	while (str[i] != c && str[i] != '\0')
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
	res = malloc (((i - j) + 1) *sizeof(char));	//leaks!!
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

char	*clear_quotes(char **str, t_env *env, int exit_code, char *tmp_ex)
{
	char 	*tmp_bef;
	char	*tmp_cont;
	char	*tmp_after;
	char	*res;
	char	c;
	
	(void)tmp_ex;
	res = ft_strdup(*str);
	c = has_quotes(res);
	if (c != '\0')
	{
		tmp_bef = fnd_dllr(cnt_b_q(res, c), env, exit_code);
		if (c == '\"')
			tmp_cont = ft_strjoin(tmp_bef, fnd_dllr(cnt_in_q(res, c), env, exit_code));
		else if (c == '\'')
				tmp_cont = ft_strjoin(tmp_bef, cnt_in_q(res, c));
		tmp_after = cnt_aft_q(res, c);
		while ((c = has_quotes(tmp_after)) != '\0') // do the tmp_bef and tmp_cont and add it to old tmp_cont?? so it wont redo the other string and clean possible ' or " might encounter?
		{
			tmp_bef = ft_strjoin(tmp_cont, fnd_dllr(cnt_b_q(tmp_after, c),env, exit_code));
			if (c == '\"')
				tmp_cont = ft_strjoin(tmp_bef, fnd_dllr(cnt_in_q(tmp_after, c), env, exit_code));
			else if (c == '\'')
				tmp_cont = ft_strjoin(tmp_bef, cnt_in_q(tmp_after, c));
			tmp_after = cnt_aft_q(tmp_after, c);
		}
		
		res = ft_strjoin(tmp_cont, fnd_dllr(tmp_after, env, exit_code));
	}
	else
		res = fnd_dllr(res, env, exit_code);
	return (res);
}


/*

lets try recursive solution so if tmp_after has content, calls again the clear quotes;

char	*clear_quotes(char **str, t_env *env, int exit_code, char *tmp_ex)
{
	char 	*tmp_bef;
	char	*tmp_cont;
	char	*tmp_after;
	char	*res;
	char	*tmp_help;
	tmp_help = NULL;
	tmp_ex = NULL;
	res = NULL;
	// 
	if (*str)
		res = ft_strdup(*str);
	if (s_has_q(res) != 0)
	{
		if (s_has_q(res) == 1)
		{
			tmp_bef = fnd_dllr(cnt_b_q(res, '\''), env, exit_code);
			tmp_cont = cnt_in_q(res, '\'');
			tmp_after = cnt_aft_q(res, '\'');
			tmp_ex = ft_strjoinplus(tmp_bef, tmp_cont);
			tmp_bef = NULL;
			if (tmp_cont != NULL)
			{
				free(tmp_cont);
				tmp_cont = NULL;
			}

		} 
		else if (s_has_q(res) == 2)
		{
			tmp_bef = fnd_dllr(cnt_b_q(res, '\"'), env, exit_code);
			tmp_cont = fnd_dllr(cnt_in_q(res, '\"'), env, exit_code);
			tmp_after = cnt_aft_q(res, '\"');
			tmp_ex = ft_strjoinplus(tmp_bef, tmp_cont);
			tmp_bef = NULL;
			if (tmp_cont != NULL)
			{
				free(tmp_cont);
				tmp_cont = NULL;
			}
		}
		if (tmp_after != NULL)
		{
			if (tmp_bef != NULL)
			{
				free(tmp_bef);
				tmp_bef = NULL;
			}
			if (s_has_q(tmp_after) != 0)
			{
				if (tmp_cont != NULL)
					free(tmp_cont);
				tmp_cont = ft_strdup(tmp_ex);
				if (tmp_ex)
				{
					free(tmp_ex);
					tmp_ex = NULL;
				}
				tmp_help = clear_quotes(&tmp_after, env, exit_code, tmp_ex);
				tmp_bef = ft_strjoin(tmp_cont, tmp_help);
				if (tmp_after)
				{
					free(tmp_after);
					tmp_after = NULL;
				}
				if (tmp_cont)
				{
					free(tmp_cont);
					tmp_cont = NULL;
				}
				if (tmp_help)
				{
					free(tmp_help);
					tmp_help = NULL;
				}
				tmp_ex = ft_strdup(tmp_bef);
				free(tmp_bef);
			}
			else
			{
				tmp_bef = ft_strjoin(tmp_ex, tmp_after);
				free(tmp_ex);
				tmp_ex = NULL;
				free(tmp_after);
				tmp_after = NULL;
				tmp_ex = ft_strdup(tmp_bef);
				free(tmp_bef);
			}
		}
		else if (!tmp_after)
		{
			tmp_help = ft_strdup(tmp_ex);
			if (tmp_ex != NULL)
				free(tmp_ex);
			tmp_ex = ft_strdup(tmp_help);
			free(tmp_help);
		}
	}
	else
		tmp_ex = fnd_dllr(res, env, exit_code);
	if (res != NULL)
	{
		free(res);
		res = NULL;
	}
	return (tmp_ex);
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

*/