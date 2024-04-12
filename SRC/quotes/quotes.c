/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/12 22:06:57 by codespace        ###   ########.fr       */
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

char	*cnt_b_q(char *str, char c)
{
	int		i;
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

char	*cnt_in_q(char *str, char c)
{
	int		i;
	int		j;
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
	res = malloc (((i - j) + 1) * sizeof(char));
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
	int		i;
	int		j;
	char	*res;

	i = 0;
	res = NULL;
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
	res = malloc (((i - j) + 1) * sizeof(char));
	i = 0;
	while (str[j] != '\0')
		res[i++] = str[j++];
	res[i] = '\0';
	return (res);
}

char	has_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return ('\0');
	}
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			return (str[i]);
		}
		i++;
	}
	return ('\0');
}

char	*clear_quotes(char **str, t_env *env, int exit_code, char *tmp_ex)
{
	char	*tmp_bef;
	char	*tmp_cont;
	char	*tmp_after;
	char	*res;
	char	*tmp_help;
	char	c;

	res = ft_strdup(*str);
	c = has_quotes(res);
	if (has_quotes(res) != '\0')
	{
		tmp_bef = fnd_dllr(cnt_b_q(res, c), env, exit_code);
		if (c == '\"')
		{
			tmp_ex = cnt_in_q(res, c);
			tmp_help = fnd_dllr(tmp_ex, env, exit_code);
			tmp_cont = ft_strjoinplus(tmp_bef, tmp_help);
			free(tmp_help);
		}
		else if (c == '\'')
		{
			tmp_ex = cnt_in_q(res, c);
			tmp_cont = ft_strjoinplus(tmp_bef, tmp_ex);
			free(tmp_ex);
			tmp_bef = NULL;
		}
		tmp_after = cnt_aft_q(res, c);
		while (has_quotes(tmp_after) != '\0')
		{
			c = has_quotes(tmp_after);
			tmp_ex = cnt_b_q(tmp_after, c);
			tmp_help = fnd_dllr(tmp_ex, env, exit_code);
			tmp_bef = ft_strjoinplus(tmp_cont, tmp_help);
			free(tmp_help);
			if (c == '\"')
			{
				tmp_ex = cnt_in_q(tmp_after, c);
				tmp_help = fnd_dllr(tmp_ex, env, exit_code);
				tmp_cont = ft_strjoinplus(tmp_bef, tmp_help);
				free(tmp_help);
			}
			else if (c == '\'')
			{
				tmp_ex = cnt_in_q(tmp_after, c);
				tmp_cont = ft_strjoinplus(tmp_bef, tmp_ex);
				free(tmp_ex);
			}
			tmp_ex = cnt_aft_q(tmp_after, c);
			free(tmp_after);
			tmp_after = tmp_ex;
		}
		free(res);
		tmp_ex = fnd_dllr(tmp_after, env, exit_code);
		res = ft_strjoinplus(tmp_cont, tmp_ex);
		free(tmp_ex);
	}
	else
	{
		tmp_ex = fnd_dllr(res, env, exit_code);
		res = tmp_ex;
	}
	return (res);
}
