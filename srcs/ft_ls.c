/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:27:13 by user              #+#    #+#             */
/*   Updated: 2020/05/02 13:53:03 by alex             ###   ########.fr       */
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


// sort по времени создания
// sort по времени изменения
// sort в обратном порядке

t_ls	*create_list(char **buff, char  *av)
{
	int     i;
	t_ls    *ls;
    char	*path;

	if (!(path = malloc(sizeof(char) * 255)))
		exit(0);
	i = 0;
	ls = NULL;
    while (buff[i])
    {
        path = ft_strcpy(path, av);
        path[ft_strlen(av)] = '/';
        path = ft_strcat(path, buff[i]);
        ls = init_struct(ls, path, buff[i]);
        ft_bzero(path, 255);
        i++;
    }
    return (ls);
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
	t_ls    *ls;

	ac = 0;
	buff = ft_ls_dir(av[1]);
    sort_name_rev(buff);
//  sort_name(buff);
    ls = create_list(buff, av[1]);
//  sort_time_create(buff, type, ls);
    int total = 0;
    while (ls)
    {
        printf("%s    ", ls->name);
        printf("%0.16s   %d\n", ls->time, ls->time_nsec);
        total += ls->st_block;
        ls = ls->next;
    }
    printf("total %d", total);
}
