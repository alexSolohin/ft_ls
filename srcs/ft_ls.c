/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 02:36:24 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/03 17:00:25 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*get_path(char *path, char *name)
{
	char 		*dir_path;
	char		*full_path;
	char 		file_in_dir[MAX_PATH];
	int 		len;

	full_path = NULL;
	if (path)
	{
		len = ft_strlen(path);
		if (path[len - 1] == '/')
		{
			while (len && path[len - 1] == '/')
				len--;
			dir_path = ft_strsub(path, 0, len + 1);
			full_path = ft_strjoin(dir_path, name);
			free(dir_path);
		}
		else
		{
			ft_bzero(file_in_dir, MAX_PATH);
			ft_strcat(ft_strcat(file_in_dir, "/"), name);
			full_path = ft_strjoin(path, file_in_dir);
		}
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
		{
			ft_putchar('\n');
			ft_ls_dir(tmp->path, tmp->flag, 1);
		}
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
		if (!init_struct(&e, f, f_path,
				f.l || f.G || f.t || f.r_cap || f.g || f.u))
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
		if (show_dir)
			ft_printf("%s:\n", dir_path);
		if (f.l || f.g)
			ft_printf("total %ld\n", total_blk(list));
		if (list)
		{
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
				ls->next ? ft_putchar('\n') : 0;
				ls = ls->next;
			}
		}
	}
}
