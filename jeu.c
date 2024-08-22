#include "card.h"

char *ask_value(char *qst)
{
	char *str = "\0";

	printf("%s", qst);
	scanf("%s", str);
	return (str);
}

int exploit(char *str)
{
	char **list_yes = malloc(10 * sizeof(char));
	if (!list_yes)
		return (-1);
	list_yes[0] = "YES";
	list_yes[1] = "yes";
	list_yes[2] = "y";
	list_yes[3] = "Y";
	list_yes[4] = "oui";
	list_yes[5] = "o";
	list_yes[6] = "OUI";
	list_yes[7] = "O";
	list_yes[8] = "\0";
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

	while (stack[i].type)
		i++;
	return (i);
}

int get_card(t_card *stack)
{
	int len = get_len(stack) - 1;
	void *tmp;

	t_card card = stack[len];
	show_card(card);
	tmp = realloc(stack, len * sizeof(t_card));
	stack = tmp;
	free(tmp);
	return (card.nbr);
}

void print_stack(t_card *stack)
{
	int i = 0;
	int len = get_len(stack);
	while (i < len)
		show_card(stack[i]);
}

