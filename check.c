/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 22:54:41 by alex              #+#    #+#             */
/*   Updated: 2020/03/22 00:53:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(int ac, char **av)
{
	// DIR  			*dir;
	// struct dirent	*entry;

	// dir = opendir(av[1]);
	// if (!dir)
	// 	exit(1);
	// while ((entry = readdir(dir)) != NULL)
	// {
	// 	printf("%s\n", entry->d_name);
	// }
	// closedir(dir);

	int i;

	i = 0;
	while (av[1][i] || av[2][i])
	{
		if (av[1][i] < av[2][i])
			printf(av[1][i]);
		else
			printf("0");
		i++;
	}
	return (0);
}
