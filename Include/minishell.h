/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:20:33 by gforns-s          #+#    #+#             */
/*   Updated: 2024/01/18 08:36:37 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <../libft/libft.h>
# include <errno.h>
# include <history.h>
# include <readline.h>
# include <signal.h>
# include <string.h>

void	handle_sigint(int sig);
void	handle_sigquit(int sig);

//##================builtins==================##

int		bi_gen(char *str);

#endif