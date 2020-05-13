/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:27:13 by user              #+#    #+#             */
/*   Updated: 2020/05/04 14:08:27 by user             ###   ########.fr       */
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

//t_ls	*create_list(char **buff, char  *av, t_flag flag)
//{
//	int     i;
//	t_ls    *ls;
//    char	*path;
//
//	if (!(path = malloc(sizeof(char) * 255)))
//		exit(0);
//	i = 0;
//	ls = NULL;
//    while (buff[i])
//    {
//        path = ft_strcpy(path, av);
//        path[ft_strlen(av)] = '/';
//        path = ft_strcat(path, buff[i]);
//        init_struct(ls, flag, path);
//        ft_bzero(path, 255);
//        i++;
//    }
//    return (ls);
//}

t_ls    *ft_ls_dir(char *av, t_flag flag, t_ls *dls)
{
	DIR				*dir;
	struct dirent 	*entry;
	t_ls            ls;
    char	        *path;

    if (!(path = malloc(sizeof(char) * 255)))
        exit(0);
	if (!(dir = opendir(av)))
        return NULL;
	while ((entry = readdir(dir)) != NULL)
	{
        path = ft_strcpy(path, av);
        path[ft_strlen(av)] = '/';
        path = ft_strcat(path, entry->d_name);
        init_struct(&ls, flag, path);
		add_ls_node(&ls, &dls);
        ft_bzero(path, 255);
	}
	closedir(dir);
    return (dls);
}

int    recursive(char *str, t_ls *rls, t_flag flag)
{
    DIR             *dir;
    struct dirent   *entry;
    char            path[255];
    t_ls            *ls;
    t_ls            ptr;
    char            **direct;


//    ls = malloc(sizeof(t_ls));
    if (!(dir = opendir(str)))
        return (1);
    while((entry = readdir(dir)) != NULL)
    {
        if (ft_strequ(entry->d_name, ".") || ft_strequ(entry->d_name, ".."))
            continue ;
        ft_strcpy(path, str);
        ft_strcat(path, "/");
        ft_strcat(path, entry->d_name);
        init_struct(&ptr, flag, path);
        if (S_ISDIR(ptr.mode))
        {
            ls = ft_ls_dir(str, flag, rls);
            merge_sort(&ls);
            while (ls)
            {
                if (ft_strequ(ls->name, ".") || ft_strequ(ls->name, "..") && !ls->flag.a)
                    continue ;
                printf("%s  ", ls->name);
                ls = ls->next;
            }
            printf("\n\n");
            printf("Dir: %s\n\n", path);
            recursive(path, rls, flag);
        }
//        else
//        {
//            printf("File: %s  ", entry->d_name);
//        }

    }
    closedir(dir);
	return (0);
}

//int		main(int ac, char **av)
//{
//	 char **buff;
//	 t_ls    *ls;
////	 char    **ptr;
//
//	ac = 0;
////    recursive(av[1]);
//	buff = ft_ls_dir(av[1]);
////    sort_name(buff);
////
////    sort_name_rev(buff);
//
//    ls = create_list(buff, av[1]);
//    sort_time_create(ls);
////    sort_equaly(ls);
//    int total = 0;
//    while (ls)
//    {
//        printf("File: %s  ", ls->name);
//        printf("Nsec: %ld\n", ls->time_nsec);
//        total += ls->st_block;
//        ls = ls->next;
//    }
//    printf("total %d", total);
//}
