/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/13 13:46:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*clear_quotes(char **str, t_env *env, int exit_code)
{
	t_tmp	tmp;
	char	*res;

	res = ft_strdup(*str);
	tmp.c = has_quotes(res);
	if (has_quotes(res) != '\0')
	{
		tmp.tmp_bef = fnd_dllr(cnt_b_q(res, tmp.c), env, exit_code);
		if (tmp.c == '\"')
			clear_q_1(&tmp, &res, env, exit_code);
		else if (tmp.c == '\'')
			clear_q_2(&tmp, &res);
		tmp.tmp_after = cnt_aft_q(res, tmp.c);
		while (has_quotes(tmp.tmp_after) != '\0')
			multi_q(&tmp, env, exit_code);
		clear_q_7(&tmp, &res, env, exit_code);
	}
	else
		clear_q_8(&tmp, &res, env, exit_code);
	return (res);
}
