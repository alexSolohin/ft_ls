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



char		*get_path(char *path, char *name)
{
	char		*full_path;
	char 		file_in_dir[MAX_PATH];

	ft_bzero(file_in_dir, MAX_PATH);
	if (*path == '\0' || ft_strncmp(path, name, ft_strlen(path)) == 0)
		full_path = ft_strdup(name);
	else
	{
		ft_strcat(ft_strcat(file_in_dir, ft_strcmp(path, "/") ? "/" : ""), name);
		full_path = ft_strjoin(path, file_in_dir);
	}
	return (full_path);
}

void 		recurcive(t_ls *list)
{
	t_ls	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, ".") == 0 || ft_strcmp(tmp->name, "..") == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		if (S_ISDIR(tmp->mode))
			ft_ls_dir(tmp->path, tmp->flag, 1);
					  tmp = tmp->next;
	}
}

static int	dir_list(t_ls **list, char *dir_path, t_flag f)
{
	t_dir	d;
	t_ls	e;
	char	*f_path;

	*list = NULL;
	if (!(d.dp = opendir(dir_path)))
	{
		printf("ft_ls: cannot open directory \'%s\': %s\n",
				dir_path, strerror(errno));
		return (0);
	}
	while ((d.dirent = readdir(d.dp)))
	{
		if (d.dirent->d_name[0] == '.' && !f.a)
			continue ;
		f_path = get_path(dir_path, d.dirent->d_name);
		if (!init_struct(&e, f, f_path, f.l || f.t || f.r_cap || f.g || f.u))
			continue ;
		add_ls_node(&e, list);
		(*list)->name = ft_strdup(d.dirent->d_name);
	}
	closedir(d.dp);
	return (1);
}

void 		ft_ls_dir(char *dir_path, t_flag f, int show_dir)
{
	t_ls	*list;

	if (dir_list(&list, dir_path, f))
	{
		if (list)
		{
			if (show_dir)
				printf("%s:\n", dir_path);
			merge_sort(&list);
			print_output(list);
			if (f.r_cap)
				recurcive(list);
			free_list(list);
		}
	}
}

void		ft_ls(t_ls *ls, int list_dir, int show_dir)
{
	if (ls)
	{
		if (!list_dir)
			print_output(ls);
		else if (S_ISDIR(ls->mode))
		{
			while (ls)
			{
				ft_ls_dir(ls->path, ls->flag, show_dir);
						  ls = ls->next;
			}
		}
	}
}

/*
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
//}*/
