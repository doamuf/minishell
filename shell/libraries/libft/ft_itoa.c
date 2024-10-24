/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:21:23 by mabdelna          #+#    #+#             */
/*   Updated: 2024/09/29 16:21:23 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ncount(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_nconv(char *buffer, int n, int i)
{
	int	j;

	j = 1;
	if (n < 0)
	{
		n *= -1;
		buffer[0] = '-';
	}
	if (n == 0)
		buffer[0] = '0';
	while (n > 0)
	{
		buffer[i - j] = (n % 10) + 48;
		n /= 10;
		j++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_itoa(int n)
{
	long long int	i;
	char			*buffer;

	i = ft_ncount(n);
	if (n == -2147483648)
	{
		buffer = ft_strdup("-2147483648");
		return (buffer);
	}
	buffer = (char *)malloc(sizeof(char) * i + 1);
	if (buffer == NULL)
		return (0);
	buffer = ft_nconv(buffer, n, i);
	return (buffer);
}
