#ifndef CARD_H
#define CARD_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
typedef struct t_card
{
	char *type;
	int nbr;
	int considered;
} t_card;

typedef struct player
{
	char *pseudo;
	int win;
	int loose;
} player;


int main_game();

void shuffle(t_card *stack);

t_card *fill(t_card *stack);

int ft_strlen(char *str);

void ft_putstr(char *str);

void ft_putchar(char c);

void ft_putnbr(int nbr);

char *ask_value(char *qst);

int exploit(char *str);

int get_len(t_card *stack);

int get_card(t_card *stack);

void print_stack(t_card *stack);

void show_card(t_card card);

#endif
