/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 07:15:26 by yciftci           #+#    #+#             */
/*   Updated: 2023/07/30 22:20:31 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	counter;
	size_t	n;

	n = ft_strlen(s1);
	if (ft_strlen(s2) > ft_strlen(s1))
		n = ft_strlen(s2);
	if (n == 0)
		return (0);
	counter = 0;
	while (counter < (n - 1))
	{
		if (s1[counter] != s2[counter])
			break ;
		counter++;
	}
	return (((unsigned char *)s1)[counter] - ((unsigned char *)s2)[counter]);
}
