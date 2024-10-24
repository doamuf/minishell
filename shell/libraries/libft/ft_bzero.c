/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:20:50 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:20:50 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dst, size_t len)
{
	size_t				i;
	unsigned char		*ptr;

	ptr = dst;
	i = 0;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
}
