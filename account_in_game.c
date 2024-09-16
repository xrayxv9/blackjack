// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   account_in_game.c                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: xray <xray@42angouleme.fr>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/30 00:13:57 by xray              #+#    #+#             //
//   Updated: 2024/09/10 19:16:05 by xray             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "lyb.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int reading(int file, char *content)
{
	char *str = malloc(1);
	if (!str)
		return (-1);
	int len = 0;
	while (read(file, str, 1))
	{
		if(content)
			content[len] = str[0];
		len++;
	}


	free(str);
	return (len);
}

int ft_atoi(char *str)
{
	int i = 0;
	int nbr = 0;
	while (str[i] == ' ' || str[i] == ':')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr);
}

int questions(char *qst)
{
	char str;
	char *list_yes = malloc(2);
	list_yes[0] = 'y';
	list_yes[1] = 'Y';
	printf("%s\n", qst);
	scanf("%c", &str);
	while ((getchar()) != '\n');
	if (str == list_yes[0] || str == list_yes[1])
	{
		free(list_yes);
		return (1);
	}

	free(list_yes);

	return (0);
}



void update_value(char *content, player *p1, int result)
{
	const char *PATH = "accounts.txt";
	int file = open(PATH, O_WRONLY);
	int len;
	int nbr = 0;
	char *str_nbr;
	int i = 0;

	if (result == 1)
		p1 ->win += 1;
	else if (result == -1)
		p1 ->loose += 1;
	while (*content)
	{
		if (*content == ':' && i != 0)
		{
			while (*content != '\n')
			{
				if (*content >= '0' && *content <= '9')
				{
					if (nbr == 0)
						nbr = p1->win;
					else
						nbr = p1->loose;
					len = int_len(nbr);
					if (len > int_len(nbr-1))
						content+=len-1;
					else
						content += len;
					str_nbr = malloc(len);
					cast(nbr, str_nbr);
					write(file, str_nbr, len);
					free(str_nbr);
				}
				else
				{
					write(file, content, 1);
					content++;
				}
			}
		}
		if (*content == p1 ->pseudo[i])
			i++;
		else
			i = 0;
		write(file, content, 1);
		content++;
	}
	close(file);
}

void analyse(char *content, player *p1, char *pseudo)
{
	int i = 0;
	int j;

	while (content[i])
	{
		j = 0;
		while (pseudo[j] == content[i + j])
		{
			j++;
			if (content[i + j + 1] == ':')
			{
				p1 -> pseudo = pseudo;
				p1 -> win = ft_atoi(content + (i + j + 1));

			while (content[i + j] != '/')
					j++;
				p1 -> loose = ft_atoi(content + (i + j + 1));
			}
		}
		i++;
	}
	if (p1 -> pseudo[0] == 't')
	{
		printf("This account doen't exist %s\n", pseudo);
		if (questions("Do you want to create it ?"))
		{
			p1 -> pseudo = pseudo;
			p1 -> win = 0;
			p1 -> loose = 0;
		}
		else
		{
			printf("You will then play as a Guest\n");
			p1 -> pseudo = "guest";
			p1 -> win = 0;
			p1-> loose = 0;
		}
	}	
}

char *file_manager()
{
	const char *PATH = "accounts.txt";
	int file = open(PATH, O_RDONLY);
	int len = reading(file, 0);
	char *content = malloc(len + 1);
	
	close(file);
	file = open(PATH, O_RDONLY);

	reading(file, content);
	content[len] = '\0';
	close(file);

	return (content);
}

int main(int argc, char **argv)
{
	player p1;
	p1.pseudo = "t";
	char *content = file_manager();
	(void)argv;
	if (argc > 2 || argc < 2)
	{
		printf("The number of argument is invalid");
		free(content);
		return (1);
	}
	analyse(content, &p1, argv[1]);
	update_value(content, &p1, 1);

	free(content);
	return (0);
}
