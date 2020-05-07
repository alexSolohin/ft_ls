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

void			strmode(mode_t mode, char *buf)
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

char	*ft_chmod(mode_t mode, t_ls *ls)
{
	char chmod[11];
	chmod[0] = set_zero_mode(mode);
	strmode(mode, &chmod[1]);
	if (mode & S_ISUID)
		chmod[3] = (chmod[3] == 'x') ? 's' : 'S';
	if (mode & S_ISGID)
		chmod[6] = (chmod[6] == 'x') ? 's' : 'S';
	if (mode & S_ISVTX)
		chmod[9] = (chmod[9] == 'x') ? 't' : 'T';
	ls->chmod = chmod;
	return (ls->chmod);
}

int				init_struct(t_ls *ls, t_flag flag, char *path)
{
	struct stat	file_stat;

	ls->path = path;
	ls->flag = flag;
	if (lstat(ls->path, &file_stat) < 0)
	{
		printf("%s; ", strerror(errno));
		return 0;
	}
	ls->gid = file_stat.st_gid;
	ls->uid=  file_stat.st_uid;
	ls->time = ls->flag.u ? file_stat.st_atim : file_stat.st_mtim;
	ls->links = file_stat.st_nlink;
	ls->byte_size = file_stat.st_size;
	ls->chmod = ft_chmod(file_stat.st_mode, ls);
	ls->d_mode = ls->chmod[0] == 'd' ? 1 : 0;
	ls->rdev = file_stat.st_rdev;
	return (1);
}
//printf("name = %s\n", ls->path);
//int major = (int)(((file_stat.st_rdev) >> 16) & 0xffff);
//("major = %4u ", major);
//printf(", minor = %4u\n", (int)((file_stat.st_rdev) & 0xffff));