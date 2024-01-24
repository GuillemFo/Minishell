/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanylev <adanylev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:51:39 by adanylev          #+#    #+#             */
/*   Updated: 2024/01/18 11:31:01 by adanylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"



int	check_sign(char	*s, t_lexer *lexer)
{
	if (!ft_strncmp(s, ">\0", 2) || !ft_strncmp(s, "<\0", 2) ||
	 !ft_strncmp(s, ">>\0", 3) || !ft_strncmp(s, "<<\0", 3) ||
	 !ft_strncmp(s, "|\0", 2))
		return(1);
	return(0);		
}