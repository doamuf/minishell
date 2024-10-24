/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:32:39 by mabdelna          #+#    #+#             */
/*   Updated: 2023/08/13 14:32:39 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t siz)
{
	void	*ptr;

	ptr = malloc(nitems * siz);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, (nitems * siz));
	return (ptr);
}
