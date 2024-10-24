/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:56:44 by mabdelna          #+#    #+#             */
/*   Updated: 2023/08/13 12:56:44 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char		*t_str1;
	unsigned char		*t_str2;
	size_t				i;

	i = 0;
	t_str1 = (unsigned char *)str1;
	t_str2 = (unsigned char *)str2;
	while (t_str1[i] && i < n)
	{
		if (t_str1[i] != t_str2[i])
			return (t_str1[i] - t_str2[i]);
		i++;
	}
	if (i != n)
		return (t_str1[i] - t_str2[i]);
	return (0);
}
