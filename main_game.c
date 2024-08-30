#include "lyb.h"

char *ask_value(char *qst)
{
	char *str = "\0";

	printf("%s", qst);
	scanf("%s", str);

	return (str);
}

int exploit(char *qst)
{
	char str;
	char *list_yes = malloc(5 * sizeof(char));
	if (!list_yes)
		return (-1);
	list_yes[0] = 'y';
	list_yes[1] = 'Y';
	list_yes[2] = 'o';
	list_yes[3] = 'O';
	list_yes[4] = '\0';
	printf("%s", qst);
	scanf("%c", &str);
	while ((getchar()) != '\n');
	for (int i = 0; list_yes[i]; i++)
	{
		if (str  == list_yes[i])
		{
			 free(list_yes);
			 return (1);
		}
	}
	free(list_yes);
	return (0);
}

int get_len(t_card *stack)
{
	int i = 0;

	while (stack[i+1].type[0] != '\0')
		i++;

	return (i);
}

int get_card(t_card *stack)
{
	int len = get_len(stack);

	t_card card = stack[len];
	show_card(card);
	stack[len].type = "\0";
	return (card.nbr);
}

void print_stack(t_card *stack)
{
	int i = 0;
	//int len = get_len(stack);
	while (stack[i].type)
	{
		show_card(stack[i]);
		i++;
	}
}

int change_eleven(t_card *stack)
{
	int len = get_len(stack);
	int i = len+1;
	while ((stack[i].nbr != 1 || stack[i].considered == 1) && stack[i].nbr != 0)
		i++;
	if (stack[i].considered == 11)
	{
		stack[i].considered = 1;
		return (1);
	}
	return (0);
}

int check_value(int val, int *ace_count, int *count, t_card *stack)
{
	char *qst;
	*count += val;
	if (*count > 21)
	{
		if (*ace_count != 0)
		{
			while (*count > 21)
			{
				if (change_eleven(stack))
				{
					*ace_count -= 1;
					*count -= 10;
				}
			}
			return (0);
		}
		if (*count > 21)
		{
			ft_putstr("You have bursted !");
			return (-1);
		}
	}
	else if (*count == 21)
	{
		ft_putstr("Congratulation, you have a blackjack");
		return (1);
	}
	else
	{
		if (val == 1)
		{
			*count -= 1;
			if (*count + 10 < 21)
			{
				qst = "Do you want your ace to be an 11 ? (can change in the future)\n";
				if (exploit(qst))
				{
					*ace_count += 1;
					*count += 11;
					stack[get_len(stack)].considered = 11;
					ft_putstr("Your ace will be treated like an 11 from now on.\n");
					if (*count == 21)
					{
						ft_putstr("Congratulations, you have a blackjack !");
						return (1);
					}
					*count -= 1;
				}
				else 
					stack[get_len(stack)].considered = 1;
			}
			*count += 1;
		}
		return (0);
	}
	return (0);
}

int main_game()
{
	int count = 0;
	int ace_count = 0;
	int running = 0;
	int nbr;
	int npc;
	t_card *stack = malloc(53 * sizeof(t_card));
	if (!stack)
		return (-1);
	fill(stack);
	shuffle(stack);	
	while (running == 0)
	{
		nbr = get_card(stack);
		running = check_value(nbr, &ace_count, &count, stack);
		if (running != 0)
			break;

		ft_putstr("Your count is at ");
		ft_putnbr(count);
		ft_putstr(" points with ");
		ft_putnbr(ace_count);
		if (ace_count != 1)
			ft_putstr(" aces\n");
		else
			ft_putstr(" ace\n");
		if (exploit("Do you want to draw another card ?\n") == 0)
			running = 1;
	}
	if (!(count >= 21))
	{
		srand(time(0));
		npc = rand() % 7;
		npc += 16;
		if (npc > 21)
			ft_putstr("You won I bursted\n");
		else if (npc == 21)
			ft_putstr("I won I got a blackjack\n");
		else
		{
			ft_putstr(" To remind you, You had ");
			ft_putnbr(count);
			ft_putstr(" points\n");
			sleep(1);
			ft_putstr("And I achieved the great ammount of..\n");
			sleep(2);
			ft_putnbr(npc);
			ft_putstr(" points\n");
			if (npc < count)
				ft_putstr("Congratulation, You won !\n");
			else if (npc > count)
				ft_putstr("Unfortunatly, You lost !\n");
			else
				ft_putstr("It's a draw !\n");
		}
	}
	free(stack);
	return (0);
}
