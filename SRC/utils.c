/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:12 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/20 13:58:01 by gforns-s         ###   ########.fr       */
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
