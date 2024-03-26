/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:12 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/26 01:51:37 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_check_max_min(char *argv)
{
	long	result;
	long	sign;
	size_t	i;

	result = 0;
	i = 0;
	sign = 1;
	if (argv[0] == '-' || argv[0] == '+' || argv[0] == ' ')
	{
		if (argv[0] == '-')
			sign = -1;
		i++;
	}
	if (argv[i] == '\0')
		return (0);
	while (argv[i])
	{
		result = result * 10 + argv[i] - '0';
		i++;
	}
	result = sign * result;
	if (result > LLONG_MAX || result < LLONG_MIN)
		return (0);
	return (1);
}

long long	ft_check_arg_is_num(char *argv)
{
	int	z;
	int	i;

	z = 0;
	i = 1;
	if (argv[0] == '-' || argv[0] == ' ' || argv[0] == '+' || (argv[0] >= '0' && argv[0] <= '9'))
	{
		while (argv[i] != '\0')
		{
			if (argv[i] == ' ' && argv[i + 1] == '\0')
				break;
			z = ft_isdigit(argv[i]);
			if (z == 0)
				return (0);
			i++;
		}
	}
	else
		return (0);
	if (ft_check_max_min(argv) == 0)
		return (0);
	return (1);
}

char	*clear_spaces(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i + 1] != ' ')
		{
			new[j] = str[i];
			j++;
		}
		else if (str[i] != ' ' && str[i + 1] == ' ')
		{
			new[j] = str[i];
			j++;
			if (str[i + 2] != '\0')
			{
				new[j] = str[i + 1];
				j++;
			}
		}
		else if (str[i] != ' ' && str[i + 1] == '\0')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}