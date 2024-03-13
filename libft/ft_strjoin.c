/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gforns-s <gforns-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:59:51 by gforns-s          #+#    #+#             */
/*   Updated: 2024/03/13 19:41:04 by gforns-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	newlen;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	newlen = ft_strlen(s1) + ft_strlen(s2);
	newstr = malloc((newlen + 1) * sizeof(char));
	if (!newstr)
		return (0);
	ft_strlcpy(newstr, s1, newlen + 1);
	ft_strlcat(newstr, s2, newlen + 1);
	return (newstr);
}

/*
int	main(void)
{
	char s1[12] = "Buenos dias";
	char s2[18] = "Esto es una prueba";

	ft_strjoin(s1, s2);
	printf("-----%s\n", ft_strjoin(s1, s2));
	printf("---%zu\n", ft_strlen(ft_strjoin(s1, s2)));
}
*/