/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:55:26 by alex              #+#    #+#             */
/*   Updated: 2020/04/18 17:24:47 by user             ###   ########.fr       */
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

//	parser to file
//	opendir(../dir)
//		while (entry = readdir())


void	ft_ls_dir(char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	// t_ls			*ls;

	dir = opendir(av);
	if (!dir)
		exit(0);
	while ((entry = readdir(dir)) != NULL)
	{

	}
	closedir(dir);
}

int     main(int ac, char **av)
{
	ac = 0;
	DIR		*dir;
	struct 	dirent	*entry;
	t_ls	*ls;
	t_ls	*ptr;
	char	*ptri;
	struct	stat	file_stat;

	ls = malloc(sizeof(t_ls));
	dir = opendir(av[1]);
	if (!dir)
		exit(0);
	ptri = malloc(sizeof(char) * 100);
	ptri = ft_strcpy(ptri, av[1]);
	ptri[ft_strlen(av[1])] = '/';
	while ((entry = readdir(dir)) != NULL)
	{

		ptr = malloc(sizeof(t_ls));
		ptr->name = ft_strdup(ptri);
		ptr->name = ft_strcat(ptr->name, entry->d_name);
		printf("%s\n", ptr->name);
		if (stat(entry->d_name, &file_stat) == -1)
			printf("bad idea\n");
		printf( (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
		printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
		printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
		printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
		printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
		printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
		printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
		printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
		printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
		printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");
		printf("\n\n");


		// ptr->next = ls;
		// ls = ptr;
		free(ptr->name);
	}
	// while (ls->next != NULL)
	// {
	// 	ft_putstr(ls->name);
	// 	if (ls->next->name != NULL)
	// 		ft_putstr("        ");
	// 	ls = ls->next;
	// }

	// if (ac == 2)
	// 	ft_ls_dir(av[1]);
}
