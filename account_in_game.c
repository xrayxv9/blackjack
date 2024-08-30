// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   account_in_game.c                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: xray <xray@42angouleme.fr>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/30 00:13:57 by xray              #+#    #+#             //
//   Updated: 2024/08/30 12:06:25 by xray             ###   ########.fr       //
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
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr *= 10 + (str[i] - 48);
		i++;
	}	
	return (nbr);
}

void analyse(char *content, player *p1)
{
	char *pseudo;
	int i = 0;
	int j;

	printf("What is your pseudo ?\n");
	scanf("%s\n", pseudo);
	while ((getchar()) != '\n');
	while (content[i])
	{
		j = 0;
		while (pseudo[j] == content[i + j])
			j++;
		if (content[i + j] == ':')
		{
			p1 -> pseudo = pseudo;
			p1 -> win = ft_atoi(content + (i + j));
		while (content[i + j] != '/')
				j++;
			p1 -> loose = ft_atoi(content + (i + j));
		}
		i++;
	}
	if (p1 -> pseudo[0] == 't')
	{
		printf("This account doen't exist %s\n", pseudo);
		if (exploit("Do you want to create it ?"))
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


int main(void)
{
	const char *PATH = "accounts.txt";
	int file = open(PATH, O_RDONLY);
	char *content = malloc(reading(file, 0));
	player p1;
	p1.pseudo = "t";
	
	close(file);
	file = open(PATH, O_RDONLY);
	reading(file, content);
	analyse(content, &p1);

	free(content);
	return (0);
}
