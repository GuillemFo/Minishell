/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:57:56 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/15 14:50:34 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void handle_sigint(int sig) 
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void handle_sigquit(int sig)
{
	(void)sig;
}

/*void	handle_gen()
{
	if (sigint == 2)
		
}

*/