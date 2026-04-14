/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:12:34 by zgtaib            #+#    #+#             */
/*   Updated: 2024/06/11 14:43:02 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_is_digit(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] < '0' || str[x] > '9')
			return (0);
		x++;
	}
	return (1);
}

static void	converting_bi(char c, int pid)
{
	int	x;
	int	bit;

	x = 7;
	while (x >= 0)
	{
		bit = (c >> x) & 1;
		if (bit == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		else if (bit == 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
		}
		usleep(70);
		usleep(70);
		x--;
	}
}

int	main(int argc, char **argv)
{
	int	x;
	int	pid;
	int	len;

	x = 0;
	if (argc != 3)
		return (1);
	x = 0;
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) == -1 || !ft_is_digit(argv[1]))
		return (1);
	if ((long long)pid > LONG_MAX || pid < 0 || pid == 0)
		return (1);
	len = ft_strlen(argv[2]) + 1;
	while (x < len)
	{
		converting_bi(argv[2][x], pid);
		x++;
	}
	return (0);
}
