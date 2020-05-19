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
			ft_ls_internal(tmp, 1);
		tmp = tmp->next;
	}
}

void 		ft_ls_dir(char *dir_path, t_flag f)
{
	t_dir	d;
	t_ls	*list;
	t_ls	e;
	char	*f_path;

	list = NULL;
	if (!(d.dp = opendir(dir_path)))
	{
		printf("%s", strerror(errno));
		return ;
	}

	while ((d.dirent = readdir(d.dp)))
	{
		if (d.dirent->d_name[0] == '.' && !f.a)
			continue ;
		f_path = get_path(dir_path, d.dirent->d_name);
		if (!init_struct(&e, f, f_path, f.l || f.t || f.r_cap || f.g || f.u))
			continue ;
		add_ls_node(&e, &list);
		list->name = ft_strdup(d.dirent->d_name);
	}
	closedir(d.dp);
	merge_sort(&list);
	print_output(list);
	if (f.r_cap)
		recurcive(list);
	free_list(list);
}

void		ft_ls_internal(t_ls *ls, int show_dir)
{
	if (show_dir)
		printf("%s:\n", ls->path);
	ft_ls_dir(ls->path, ls->flag);
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
				ft_ls_internal(ls, show_dir);
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

t_ls	*create_list(char **buff, char  *av, t_flag flag)
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

t_ls    *ft_ls_dir(char *av)
{
	DIR				*dir;
	struct dirent 	*entry;
	char			**buff;
	t_ls            *ls;
	int 			i;
	int				j;

	if (!(dir = opendir(av)))
        return (NULL);
	i = size_buff(av);
	buff = (char**)malloc(sizeof(char*) * i + 1);
	j = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		buff[j++] = ft_strdup(entry->d_name);
	}
	buff[j] = NULL;
	ls = create_list(buff, av);
	closedir(dir);
	return(ls);
}

int    recursive(char *str)
{
    DIR             *dir;
    struct dirent   *entry;
    char            path[255];
    t_ls            *ls;
    char            **direct;


    ls = malloc(sizeof(t_ls));
    if (!(dir = opendir(str)))
        return (1);
//    while((entry = readdir(dir)) != NULL)
//        printf(entry->d_name);
    while((entry = readdir(dir)) != NULL)
    {
        if (ft_strequ(entry->d_name, ".") || ft_strequ(entry->d_name, ".."))
            continue ;
        ft_strcpy(path, str);
        ft_strcat(path, "/");
        ft_strcat(path, entry->d_name);
        init_struct(ls, buff, entry->d_name);
        if (ls->mode == 'd')
        {
            printf("Dir: %s\n\n", path);
            direct = ft_ls_dir(path);
            ls = create_list(direct, str);
            int i = 0;
            while (direct[i])
            {
                print_output(ls);
                ls = ls->next;
            }
            printf("\n\n");
            recursive(path);
        }
        else
        {
            printf("File: %s  ", entry->d_name);
        }
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
