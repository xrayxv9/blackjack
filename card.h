#ifndef CARD_H
#define CARD_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;

	return (i);
}

void ft_putstr(char *str)
{
	int len = ft_strlen(str);
	
	write(1, str, len);
}

void ft_putchar(char c)
{
	write(1, &c,1);
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
	else if (nbr < 10)
	{
		ft_putchar(nbr + 48);
	}
}
typedef struct	t_card
{
	char	*type;
	int		nbr;
} t_card;

char *ask_value(char *qst);

int exploit(char *str);

int get_len(t_card *stack);

int get_card(t_card *stack);

void print_stack(t_card *stack);

void show_card(t_card card);



#endif
