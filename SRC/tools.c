/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:10 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/12 17:27:55 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errno_printer(char *com, char *error_txt, char *asked)
{
	ft_putstr_fd("Minishell:", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(error_txt, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(asked, 2);
	write(2, "\n", 1);
	return (0);
}


char *trim_bef(char *str, char c) {
    int i = 0;
    while (str[i] != c && str[i] != '\0')
        i++;
    char *new_str = malloc((i + 1) * sizeof(char));
    if (!new_str)
        return NULL;
    memcpy(new_str, str, i);
    new_str[i] = '\0';
    return new_str;
}


char *trim_after(char *str, char c) {
    int i = 0;
    
    // Find the first occurrence of 'c'
    while (str[i] != c && str[i] != '\0')
        i++;

    // If 'c' is not found, return an empty string
    if (str[i] == '\0') {
        char *empty_str = malloc(sizeof(char));
        if (!empty_str)
            return NULL;
        empty_str[0] = '\0';
        return empty_str;
    }

    // Find the length of the substring after 'c'
    int x = 0;
    while (str[i] != '\0') {
        x++;
        i++;
    }

    // Allocate memory for the new string
    char *new_str = malloc((x + 1) * sizeof(char));
    if (!new_str)
        return NULL;

    // Copy the substring after 'c'
    i -= x;
    x = 0;
    while (str[++i] != '\0') {
        new_str[x] = str[i];
        x++;
    }
    new_str[x] = '\0';

    return new_str;
}
