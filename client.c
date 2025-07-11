/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:36:50 by pahernan          #+#    #+#             */
/*   Updated: 2025/07/03 17:36:50 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	write(1, str, i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
	{
		i++;
	}
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j++;
		i++;
	}
	while ((str[i]) && (str[i] >= '0' && str[i] <= '9'))
	{
		res = str[i] - '0' + res * 10;
		i++;
	}
	if (j % 2 != 0)
		res = -res;
	return (res);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	send_signal(int pid, unsigned char character)
{
	int				i;
	int				bit;

	i = 7;
	while (i >= 0)
	{
		bit = (character >> i) & 1;
		if (bit == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		usleep(1000);
	}
}

int	main(int ac, char *av[])
{
	pid_t	server_pid;
	int		i;

	if (ac != 3)
	{
		ft_putstr("Error: Necesita 3 argumentos.");
		exit(0);
	}
	if (!is_digit(av[1]))
	{
		ft_putstr("Error: El PID debe ser numérico.\n");
		exit(0);
	}
	server_pid = ft_atoi(av[1]);
	if (kill(server_pid, 0) == -1)
	{
		ft_putstr("Error: El proceso con ese PID no existe.\n");
		exit(0);
	}
	i = 0;
	while (av[2][i])
		send_signal(server_pid, (unsigned char)av[2][i++]);
	send_signal(server_pid, '\0');
	return (0);
}
