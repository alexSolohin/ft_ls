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
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

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

char	*ft_chmod(t_ls *ls)
{
//	char chmod[11];

	ls->chmod[0] = set_zero_mode(ls->mode);
	ft_strmode(ls->mode, &(ls->chmod[1]));
	if (ls->mode & S_ISUID)
		ls->chmod[3] = (ls->chmod[3] == 'x') ? 's' : 'S';
	if (ls->mode & S_ISGID)
		ls->chmod[6] = (ls->chmod[6] == 'x') ? 's' : 'S';
	if (ls->mode & S_ISVTX)
		ls->chmod[9] = (ls->chmod[9] == 'x') ? 't' : 'T';
	ls->chmod[10] = '\0';
	return (ls->chmod);
}

int				init_struct(t_ls *ls, t_flag flag, char *path)
{
	struct stat	file_stat;

	ls->name = path;
	ls->flag = flag;
	if (lstat(ls->name, &file_stat) < 0)
	{
		printf("Not valid file \n");
		return 0;
	}
	ls->mode = file_stat.st_mode;
	ls->gid = file_stat.st_gid;
	ls->uid=  file_stat.st_uid;
	ls->time = ls->flag.u ? file_stat.st_atimespec : file_stat.st_mtimespec;
	ls->nlink = file_stat.st_nlink;
	ls->byte_size = file_stat.st_size;
	ls->rdev = file_stat.st_rdev;
	ls->next = NULL;
	return (1);
}
