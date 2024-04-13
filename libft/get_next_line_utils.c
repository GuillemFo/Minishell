/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:10:04 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/08 11:54:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlenplus(char *var)
{
	size_t	count;

	count = 0;
	if (!var)
		return (0);
	while (var[count] != '\0')
		count++;
	return (count);
}

char	*ft_strdupplus(char *s1)
{
	size_t	s1l;
	char	*str;
	int		i;

	if (!s1)
		return (0);
	i = 0;
	s1l = ft_strlen(s1);
	str = malloc ((s1l + 1) * sizeof(char));
	if (!str)
		return (free (s1), NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoinplus(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdupplus(s2));
	if (!s2)
	{
		newstr = ft_strdupplus(s1);
		free(s1);
		return (newstr);
	}
	newstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!newstr)
		return (free (s1), free (s2), NULL);
	i = -1;
	while (s1[++i] != '\0')
		newstr[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		newstr[i + j] = s2[j];
	newstr[i + j] = '\0';
	if (s1)
		free (s1);
	return (newstr);
}

int	ft_strchrplus(char *var, int c)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	while (var[i] != '\0' && var[i] != (char) c)
		i++;
	if (var[i] != (char) c)
		return (0);
	return (1);
}
