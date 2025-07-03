/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:37:00 by pahernan          #+#    #+#             */
/*   Updated: 2025/07/03 17:37:00 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putchar(int nb)
{
	write(1, &nb, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	ft_putchar (nb + '0');
}

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


void	signal_chek(int signal)
{
	static unsigned char	char_atm = 0;
	static int				index_bit = 0;

	char_atm |= (signal == SIGUSR1);
	index_bit++;
	if (index_bit == 8)
	{
		if (char_atm == '\0')
			ft_putchar('\n');
		else
			ft_putchar(char_atm);
		index_bit = 0;
		char_atm = 0;
	}
	else
		char_atm <<= 1;
}

int	main(void)
{
	ft_putstr("PID : ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	signal(SIGUSR1, signal_chek);
	signal(SIGUSR2, signal_chek);
	while (1)
		pause();
	return (0);
}
