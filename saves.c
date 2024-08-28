// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   saves.c                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: xray <xray@42angouleme.fr>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/28 10:23:41 by xray              #+#    #+#             //
//   Updated: 2024/08/28 11:59:38 by xray             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "card.h"

int reading(int file, char *ptr);

int main(void)
{
	const char *PATH = "txt.txt";
	int file = open(PATH, O_RDONLY);
	char *str=malloc(reading(file, 0));
	if (!str)
		return (1);
	close(file);
	file = open(PATH, O_RDONLY);
	reading(file, str);

	free(str);
	close (file);
	return (0);
}

int reading(int file, char *ptr)
{
	int len;
	char *c = malloc(1);

	len = 0;
	while (read(file, c, 1))
	{
		if (ptr)
		{
			ptr[len] = c[0];		
		}
		len++;
	}
	free(c);
	return (len);
}
