/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:43:38 by mabdelna          #+#    #+#             */
/*   Updated: 2023/08/13 12:24:22 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	index;

	index = ft_strlen(src);
	i = 0;
	if (!dst || !siz)
		return (index);
	if ((index + 1 < siz))
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	else if (siz != 0)
	{
		while (i < siz - 1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (index);
}
