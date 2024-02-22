/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/02/22 12:28:12 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*after_q(char *str, char c)
{
	int	i;
	int	start;
	char	*ret;
	
	i = 0;
	while (str[i] != c)
		i++;
	i++;
	while (str[i] != c)
		i++;
	if (str[i] == '\0')
		return (ft_strdup("?"));
	start = i + 1;
	while (str[i] != '\0')
		i++;
	ret = malloc(((i - start) + 1) * sizeof(char));
	i = 0;
	while (str[start] != '\0')
	{
		ret[i] = str[start];
		start++;
		i++;
	}
	ret[i] = '\0';
	printf("aft:%s:\n", ret);
	return(ret);
}

char	*content_q(char *str, char c)
{
	int	i;
	int	j;
	int	start;
	char *ret;
	i = 0;
	while (str[i] != c)
		i++;
	if (str[++i] == c)
		return (ft_strdup(""));
	start = i;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (i < 1)
		i = 1;
	ret = malloc (((i - start) + 1) * sizeof(char));
	j = i - start;
	i = 0;
	while (str[start] != c && j > i)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	printf("cont:%s:\n", ret);
	return (ret);
}


char	*before_q(char *str, char c)
{
	int	i;
	char	*ret;
	i = 0;
	while (str[i] != c)
		i++;
	if (i < 1)
		return(ft_strdup(""));
	ret = malloc((i + 1) * sizeof(char));
	ft_strncpy(ret, str, i);
	printf("bef:%s:\n", ret);
	return (ret);
}

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
	return (str[i]);
}


//maybe iterate and check if it has quotes before trying to clean them??
char	*clear_quotes(char *str)
{
	int		i;
	char	c;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	
	tmp3 = ft_strdup(str);
	i = 0;
	if (tmp3)
	{
		while((c = has_quotes(tmp3)) != '\0')
		{
			if (c == '\0')
				return (tmp3);
			tmp = before_q(tmp3, c);
			tmp2 = ft_strjoin(tmp, content_q(tmp3, c));
			tmp3 = ft_strjoin(tmp2, after_q(tmp3, c));
		}
		return (tmp3);
	}
	return (ft_strdup("ERROR?????\n"));
}
