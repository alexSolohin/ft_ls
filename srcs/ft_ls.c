/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:27:13 by user              #+#    #+#             */
/*   Updated: 2020/04/30 14:57:07 by user             ###   ########.fr       */
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

void	print(char **buff, t_type type, char  *av)
{
	int i;
	t_ls *ls;

	//stat
	struct stat 	file_stat;
    char			*path;

	if (!(path = malloc(sizeof(char) * 255)))
		exit(0);
	i = 0;
	if (type.flag == 'l')
	{
		while (buff[i])
		{
			path = ft_strcpy(path, av);
			path[ft_strlen(av)] = '/';
			path = ft_strcat(path, buff[i]);
			if (ft_strequ(av, ".") || ft_strequ(av, ".."))
			{
			if (stat(buff[i], &file_stat) < 0)
				exit(0);
			}
			else
			{
				if (stat(path, &file_stat) < 0)
					exit(0);
			}
			ls = init_struct(path, buff[i]);
			int j = 0;
			while (j < 10)
			{
				printf("%c", ls->chmod[j++]);
			}
			printf(" %d ", ls->links);
			printf(" %s %s %d %s ",   ls->user_name, ls->group_name, ls->byte_size,ls->name);
			printf("%.16s\n", ls->time);
			ft_bzero(path, 255);
			i++;
		}
	}
}

int		size_buff(char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	dir = opendir(av);
	while ((entry = readdir(dir)) != NULL)
	{
		i++;
	}
	closedir(dir);
	return(i);
}

char	**ft_ls_dir(char *av)
{
	DIR				*dir;
	struct dirent 	*entry;
	char			**buff;
	int 			i;
	int				j;

	if (!(dir = opendir(av)))
		exit(0);
	i = size_buff(av);
	buff = (char**)malloc(sizeof(char*) * i + 1);
	j = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		buff[j++] = ft_strdup(entry->d_name);
	}
	closedir(dir);
	return(buff);
}

int		main(int ac, char **av)
{
	char **buff;
	t_type	type;

	ac = 0;
	type.flag = 'l';
	buff = ft_ls_dir(av[1]);
	print(buff, type, av[1]);
}
