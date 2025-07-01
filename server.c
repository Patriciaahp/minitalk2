#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void signal_chek(int signal)
{
    static unsigned char char_atm = 0;
    static int index_bit = 0;

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

void ft_putnbr(int n)
{
    if (n == -2147483648)
    {
        write(1, "-2147483648", 11);
        return;
    }
    if (n < 0)
    {
        ft_putchar('-');
        n = n * -1;
    }
    if (n > 9)
    {
        ft_putnbr(n / 10);
        n = n % 10;
    }
    ft_putchar(n + '0');
}

void ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    write(1, str, i);
}

int main(void)
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