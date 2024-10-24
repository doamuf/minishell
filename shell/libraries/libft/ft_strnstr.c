/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:00:25 by mabdelna          #+#    #+#             */
/*   Updated: 2023/08/13 13:00:25 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	lg;
	size_t	bg;
	size_t	i;
	size_t	j;

	i = 0;
	lg = ft_strlen(lit);
	bg = ft_strlen(big);
	if (lg == 0)
		return ((char *)big);
	if (len == 0 || len < lg || bg < lg)
		return (NULL);
	while (big[i] && i <= len - lg)
	{
		j = 0;
		while (big[i + j] == lit[j] && lit[j] && (i + j) < len)
			j++;
		if (j == lg)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
