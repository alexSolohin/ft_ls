/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:55:26 by alex              #+#    #+#             */
/*   Updated: 2020/04/15 15:39:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void	ft_ls_dir(char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	t_ls			*ls;

	av = 0;
	dir = opendir("srcs");

	if (!(ls = malloc(sizeof(t_ls))))
		exit(0);
	if (!dir)
		exit(0);
	while ((entry = readdir(dir)) != NULL)
	{
		ls->name = entry->d_name;
		init_struct(ls, entry->d_name);
		printf("%s	", ls->name);
		int i = 0;
		while (i < 10)
		{
			printf("%c", ls->chmod[i]);
			i++;
		}
		printf("\t%d", ls->links);
		printf("\t%s\t%s\t%d", ls->user_name, ls->group_name, ls->byte_size);
		printf("\t%.16s %s\n", ls->time, ls->name);
	}
	closedir(dir);
}

int     main(int ac, char **av)
{
	t_ls	*ls;

	av = 0;
	if (!(ls = malloc(sizeof(t_ls))))
		exit(0);
	if (ac == 1)
		ft_ls_dir(".");
}
