#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int ft_atoi(const char *str)
{
    int num;
    int signe;
    int negatif;

    negatif = 1;
    signe = 0;
    num = 0;
    while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n' || *str == '\f' || *str == '\r')
        str++;
    while (*str == '-' || *str == '+')
    {
        if (*str == '-')
            negatif = -1;
        signe++;
        if (signe > 1)
            return (0);
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        num = num * 10 + (*str++ - '0');
    }
    return (num * negatif);
}

void send_signal(int pid, unsigned char character)
{
    unsigned char temp;
    int i;

    i = 7;
    temp = character;
    while (i >= 0)
    {
        temp = character >> i;
        if (temp % 2 == 0)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        i--;
        usleep(800);
    }
}

void ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    write(1, str, i);
}

int main(int ac, char **av)
{
    pid_t server_pid;
    int i;

    if (ac != 3)
    {
        ft_putstr("erreur pid str");
        exit(0);
    }
    server_pid = ft_atoi(av[1]);
    i = 0;
    while (av[2][i])
    {
        send_signal(server_pid, (unsigned char)av[2][i]);
        i++;
    }
    send_signal(server_pid, '\0');
    return (0);
}