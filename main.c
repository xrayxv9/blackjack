#include "card.h"

char	*type_change(int ty)
{
	if (ty == 1)
		return ("diamond");
	else if (ty == 2)
		return ("club");
	else if (ty == 3)
		return ("heart");
	else if (ty == 4)
		return ("spade");
	else
		return ("error");
}

void ft_swap(t_card *stack, int ind, int ind2)
{
	char *temp_ty = stack[ind].type;
	int temp_n = stack[ind].nbr;

	stack[ind].type = stack[ind2].type;
	stack[ind].nbr = stack[ind2].nbr;

	stack[ind2].type = temp_ty;
	stack[ind2].nbr = temp_n;
}

void show_card(t_card card)
{
	ft_putnbr(card.nbr);
	ft_putstr(" of ");
	ft_putstr(card.type);
	ft_putstr("\n");
}

void shuffle(t_card *stack)
{
	srand(time(0));
	int rando = rand() % 52;
	int i = 0;
	int ran = rand() % 100;
	int j = 0;
	while (j <= ran)
	{
		while (stack[i].type)
		{
			ft_swap(stack, i, rando);
			i++;
		}
		j++;
	}
}

t_card	*fill(t_card *stack)
{
	int i = 1;
	int j;
	int count = 0;
	t_card card; 
	while (i <= 4)
	{
		j = 1;
		while (j <= 13)
		{
			card.type = type_change(i);
			if (j >= 10)
				card.nbr = 10;
			else 
				card.nbr = j;
		j++;
		stack[count] = card;
		count++;	
		}
		i++;
	}
	card.type = 0;
	card.nbr = 0; 
	return (stack);	
}

int	main()
{
	int count = 0;
	srand(time(0));
	t_card *stack = malloc(53 * sizeof(struct t_card));
	if (!stack)
		return (1);
	fill(stack);
	shuffle(stack);
	print_stack(stack);
	count = get_card(stack);
	ft_putnbr(count);
	print_stack(stack);




	free(stack);

	return (0);
}
