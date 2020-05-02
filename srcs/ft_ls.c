/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:27:13 by user              #+#    #+#             */
/*   Updated: 2020/05/01 13:34:34 by alex             ###   ########.fr       */
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

int sort_al(char *a, char *b)
{
	int i;

	i = 0;
	while(a[i])
	{
		if (a[i] > b[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	sort_arr(char **buff, t_type type)
{
	type.dir = 0;
	size_t  i;
	size_t  j;
	size_t  n;
	char    *ptr;


	n = 0;
	while(buff[n])
	    n++;
	i = 0;
	while (i < n)
    {
	    j = 0;
	    while (j < n - i -1)
        {
	        if (ft_strcmp(buff[j], buff[j + 1]) > 0)
	        {
	            ptr = buff[j];
	            buff[j] = buff[j + 1];
	            buff[j + 1] = ptr;
            }
	        j++;
        }
	    i++;
    }
    i = 0;
	while(buff[i])
    {
        printf("%s\n", buff[i++]);
    }

	//здесь будет сортировка по имени или в зависимости от ключа
}

void	print(char **buff, t_type type, char  *av)
{
	int i;
	t_ls *ls;

	//stat
	// struct stat 	file_stat;
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
	sort_arr(buff, type);
	// print(buff, type, av[1]);
}
