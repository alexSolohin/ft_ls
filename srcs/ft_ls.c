/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:55:26 by alex              #+#    #+#             */
/*   Updated: 2020/04/20 15:26:08 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>


//	parser to file
//	opendir(../dir)
//		while (entry = readdir())


void	ft_ls_dir(char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;
	t_ls			*ls;
	t_ls			*ptr;
	int				total;

	if (!(ls = malloc(sizeof(t_ls))))
		exit(0);
	dir = opendir(av);
	if (!dir)
		exit(0);
	if (!(path = malloc(sizeof(char))))
		exit(0);
	path = ft_strcpy(path, av);
	path[ft_strlen(av)] = '/';
	total = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		ptr = malloc(sizeof(t_ls));
		ptr->name = entry->d_name;
		ptr->path = ft_strdup(path);
		ptr->path = ft_strcat(ptr->path, entry->d_name);
		init_struct(ptr);
		total += ptr->byte_size / 1000;
		ptr->next = ls;
		ls = ptr;
		free(ptr->path);

	}
	printf("total %d\n", total);
	while (ls->next != NULL)
	{
		int i = 0;
		while (i < 10)
			printf("%c", ls->chmod[i++]);
		printf(" %d %s %s", ls->links, ls->group_name, ls->user_name);
		printf(" %d %.16s %s\n", ls->byte_size, ls->time, ls->name);
		ls = ls->next;
	}
	closedir(dir);
}

int     main(int ac, char **av)
{
	ac = 0;
	ft_ls_dir(av[1]);
}
