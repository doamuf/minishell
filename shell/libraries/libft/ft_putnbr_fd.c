/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:12:26 by mabdelna          #+#    #+#             */
/*   Updated: 2023/08/18 20:12:26 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2147483648", 10);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd((n / 10), fd);
		n %= 10;
		n += 48;
		write(fd, &n, 1);
	}
	else
	{
		n = n + 48;
		write(fd, &n, 1);
	}
	return ;
}

// #include <fcntl.h>
// int main(void)
// {
//     int fd;
//     int i = 123456789;
//     fd = open("M42.txt", O_WRONLY | O_CREAT | _O_TRUNC, 0777);
//     ft_putnbr_fd(i, fd);
//     close(fd);
// }
