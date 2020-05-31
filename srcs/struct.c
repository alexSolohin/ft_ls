/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 12:54:07 by user              #+#    #+#             */
/*   Updated: 2020/04/23 16:23:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char 	set_zero_mode(mode_t mode)
{
	char file_mode;
	if (S_ISREG(mode))
		file_mode = '-';
	else if (S_ISBLK(mode))
		file_mode = 'b';
	else if (S_ISCHR(mode))
		file_mode = 'c';
	else if (S_ISDIR(mode))
		file_mode = 'd';
	else if (S_ISFIFO(mode))
		file_mode = 'p';
	else if (S_ISLNK(mode))
		file_mode = 'l';
	else if (S_ISSOCK(mode))
		file_mode = 's';
	else
		file_mode = '?';
	return (file_mode);
}

void			ft_strmode(mode_t mode, char *buf)
{
	const char	chars[] = "rwxrwxrwx";
	int			i;

	i = 0;
	while (i < 9)
	{
		buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
		i++;
	}
	buf[9] = '\0';
}

char		*ft_chmod(mode_t mode)
{
	char	chmod[11];
	chmod[0] = set_zero_mode(mode);
	ft_strmode(mode, &(chmod[1]));
	if (mode & S_ISUID)
		chmod[3] = (chmod[3] == 'x') ? 's' : 'S';
	if (mode & S_ISGID)
		chmod[6] = (chmod[6] == 'x') ? 's' : 'S';
	if (mode & S_ISVTX)
		chmod[9] = (chmod[9] == 'x') ? 't' : 'T';
	chmod[10] = '\0';
	return (ft_strdup(chmod));
}

t_ls 			*pre_stat(t_ls *ls, char *path, t_flag flag)
{
	ls->path = path;
	ls->name = NULL;
	ls->gname = NULL;
	ls->uname = NULL;
	ls->chmod = NULL;
	ls->link = NULL;
	ls->tm = NULL;
	ls->color = NULL;
	ls->flag = flag;
	return (ls);
}

int				init_struct(t_ls *ls, t_flag flag, char *path, int dostat)
{
	struct stat	file_stat;

	ls = pre_stat(ls, path, flag);
	if (!dostat)
		return (1);
	if (lstat(ls->path, &file_stat) < 0)
	{
		printf("ft_ls: cannot access \'%s\': %s\n",
				ls->name ? ls->name : ls->path, strerror(errno));
		return 0;
	}
	ls->mode = file_stat.st_mode;
	ls->chmod = ft_chmod(ls->mode);
//	ls->color = color_file(ls->mode, flag.G);
	ls->gname = get_group_name(file_stat.st_gid);
	ls->uname =  get_user_name(file_stat.st_uid);
	ls->time = ls->flag.u ? file_stat.st_atim : file_stat.st_mtim;
	ls->tm = get_tm(ls->time);
	ls->nlink = file_stat.st_nlink;
	ls->link = lpath(ls->path, ls->mode);
	ls->size = file_stat.st_size;
	ls->block = file_stat.st_blocks;
	ls->rdev = file_stat.st_rdev;
	ls->next = NULL;
	return (1);
}
