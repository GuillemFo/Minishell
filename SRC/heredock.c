/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:21:01 by gforns-s          #+#    #+#             */
/*   Updated: 2024/04/13 14:30:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_name(char **filename, int *i)
{
	char		*num;

	*i = *i + 1;
	num = ft_itoa(*i);
	*filename = ft_strjoin("tmp/SRC/.hd", num);
	free (num);
}

void	do_heredock(t_redir *tmp, char *filename, t_env *env, int exit_code)
{
	char		*nl_h;
	int			fd;
	char		*tmp2;

	fd = -1;
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	nl_h = readline("> ");
	while (nl_h && ft_strcmp(nl_h, tmp->dest) != 0)
	{
		tmp2 = fnd_dllr(nl_h, env, exit_code);
		nl_h = ft_strjoin(tmp2, "\n");
		ft_putstr_fd(nl_h, fd);
		free(tmp2);
		free (nl_h);
		nl_h = readline("> ");
	}
	close (fd);
	free(nl_h);
}

int	heredock(t_parser **parser, t_env *env, int exit_code)
{
	t_parser	*iter;
	t_redir		*tmp;
	int			i;
	char		*filename;

	i = -1;
	iter = *parser;
	while (iter)
	{
		tmp = iter->redir;
		while (tmp && tmp->dest)
		{
			if (tmp->sign == LESSLESS)
			{
				do_name(&filename, &i);
				do_heredock(tmp, filename, env, exit_code);
				if (tmp->dest)
					free(tmp->dest);
				tmp->dest = filename;
			}
			tmp = tmp->next;
		}
		iter = iter->next;
	}
	return (0);
}

/*
#include "minishell.h"

int	heredock(t_parser *parser, t_env *env, int exit_code)
{
	t_parser *iter;
	t_redir *tmp;
	int		i;
	char *nl_h;
	char *filename;
	char	*num;
	int		fd;

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
	return (999);
}

*/