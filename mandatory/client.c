/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:12:34 by zgtaib            #+#    #+#             */
/*   Updated: 2024/04/26 15:34:36 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void converting_bi(char c, int pid)
{
	int x;
	int bit;

	x = 7;
	while (x >= 0)
	{
		bit = (c >> x) & 1;
		if (bit == 0)
			kill(pid, SIGUSR1);
		else if (bit == 1)
			kill(pid, SIGUSR2);
		usleep(70);
		usleep(70);
		x--;
	}
}
static 	int	check_pid(char *arg)
{
	int x;

	x = 0;
	while(arg[x] != '\0')
	{
		if ((arg[x] >= 'a' && arg[x] <= 'z') \
		|| (arg[x] >= 'A' && arg[x] <= 'Z'))
			return (0);
		x++;
	}
	return (1);
}

int main(int argc , char **argv)
{
	int x;
	int pid; 
	
	x = 0;
	if (argc != 3)
		return (1);
	if (!check_pid(argv[1]))
		return (1);
	x = 0;
	pid = ft_atoi(argv[1]);
	if ((long long)pid > LONG_MAX || pid < 0 || pid == 0)
		return (1);
	while(argv[2][x] != '\0')
	{
		converting_bi(argv[2][x], pid);
		x++;
	} 
}       
