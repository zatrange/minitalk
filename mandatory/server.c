/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:13:17 by zgtaib            #+#    #+#             */
/*   Updated: 2024/06/22 15:39:57 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	write_byte(int *i, char *bit)
{
	if (*i == 0)
	{
		if (*bit == '\0')
			write(1, "\n", 1);
		else
			write(1, bit, 1);
		*i = 8;
		*bit = 0;
	}
}

void	handler(int sig, siginfo_t *info, void *con)
{
	static char	bit;
	static int	i = 7;
	static int	pid;

	(void)con;
	if (pid == 0)
		pid = info->si_pid;
	else if (info->si_pid != pid)
	{
		pid = info->si_pid;
		i = 7;
		bit = 0;
	}
	if (sig == SIGUSR2)
		bit |= (1 << i);
	else if (sig == SIGUSR1)
		bit |= (0 << i);
	write_byte(&i, &bit);
	i--;
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
	{
		pause();
	}
}
