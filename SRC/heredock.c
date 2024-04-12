/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:21:01 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/12 15:47:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredock(t_parser *parser, t_env *env, int exit_code)
{
	t_parser	*iter;
	t_redir		*tmp;
	int			i;
	char		*nl_h;
	char		*filename;
	char		*num;
	int			fd;

	i = 0;
	iter = parser;
	while (iter)
	{
		tmp = iter->redir;
		if (tmp && tmp->dest)
		{
			if (tmp->sign == LESSLESS)
			{
				num = ft_itoa(i);
				filename = ft_strjoin("tmp/SRC/.hd", num);
				free (num);
				fd = -1;
				fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
				nl_h = readline("> ");
				while (nl_h && ft_strcmp(nl_h, tmp->dest) != 0)
				{
					num = fnd_dllr(nl_h, env, exit_code);
					nl_h = ft_strjoin(num, "\n");
					ft_putstr_fd(nl_h, fd);
					free(num);
					free (nl_h);
					nl_h = readline("> ");
				}
				close (fd);
				free(nl_h);
			}
			i++;
			if (tmp->dest)
				free(tmp->dest);
			tmp->dest = filename;
		}
		iter = iter->next;
	}
	return (0);
}
