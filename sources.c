#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

void ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putnbr(int nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		ft_putnbr(-nbr);
	}
	else if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else if (nbr <= 9)
	{
		ft_putchar(nbr + '0');
	}
}

int char_len(char *str)
{
        int i = 0;
        while (str[i])
                i++;
        return (i);
}

int int_len(int nbr)
{
        if (nbr >= 10)
                return (1 + int_len(nbr / 10));
        return (1);
}

char *cast(int nbr, char *str)
{
        int len = int_len(nbr);
        int i = 0;
		int ind_nbr;
		while (i <= len)
        {
				if (nbr >= 10)
				{
					ind_nbr = nbr / 10;
					while (ind_nbr >= 10)
						ind_nbr /= 10;
					nbr %= 10;

				}
				else
					ind_nbr = nbr;
				str[i] = ind_nbr + '0';
				i++;
        }
        str[len] = '\0';
        return (str);
}

