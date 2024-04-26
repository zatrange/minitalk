/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:13:17 by zgtaib            #+#    #+#             */
/*   Updated: 2024/04/20 14:11:06 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int converting_back(int pid, int x, int *hold)
{	
	int i;
	int ascii;
	
	if (x == 8)
	{	
		x = 0;
		i = 0;
		ascii = 0;
		while (i < 8)
		{
			ascii |= hold[i] << (7 - i);
			i++;
		}
		if (ascii == '\0')
		{	
			free(hold);
			kill(pid, SIGUSR1);
			write(1, "\n", 1);
		}
		else 	
			write(1, &ascii, 1);
	}
	return (x);
}
void handler(int sig, siginfo_t *info, void *con)
{
	static int	*hold;
	static int	x; 
	static int	pid;
	
	(void)con;	
	if(info->si_pid != pid)
	{
		x = 0;
		hold = NULL;  
	}
	pid = info->si_pid;
	 if (hold == NULL)
	 	hold = malloc(8 * sizeof(int));
			if(!hold)
				exit(1);
	if (sig == SIGUSR1)
		hold[x] = 0;
	else if (sig == SIGUSR2)
		hold[x] = 1;
	x++;
	x = converting_back(pid, x, hold);
}
int main()
{	
	struct sigaction sa;
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO; 
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);	
	while (1)
	{
		pause();
	}
}
