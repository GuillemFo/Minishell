/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:22:21 by adanylev          #+#    #+#             */
/*   Updated: 2024/02/15 14:43:57 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	parser_size(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser != NULL)
	{
		parser = parser->next;
		i++;
	}
	return (i);
}

char	**env_to_char(t_env	*env)
{
	char	**new_env;
	
}

void	exec_error(char	*message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}