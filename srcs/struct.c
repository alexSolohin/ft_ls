/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 12:54:07 by user              #+#    #+#             */
/*   Updated: 2020/06/04 19:57:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

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

char	ft_acl(t_ls *ls)
{
	acl_t		acl;
	acl_entry_t dummy;
	ssize_t		xattr;
	char		chr;

	xattr = 0;
	acl = acl_get_link_np(ls->path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
	    acl_free(acl);
	    acl = NULL;
	}
    xattr = listxattr(ls->path, NULL, 0, XATTR_NOFOLLOW);
    if (xattr < 0)
        xattr = 0;
    if (xattr > 0)
        chr = '@';
    else if (acl != NULL)
        chr = '+';
    else
        chr = ' ';
	acl_free(acl);
    return (chr);
}

char	*ft_chmod(t_ls *ls)
{
    char chmod[12];
	chmod[0] = set_zero_mode(ls->mode);
	ft_strmode(ls->mode, &(chmod[1]));
	if (ls->mode & S_ISUID)
		chmod[3] = (chmod[3] == 'x') ? 's' : 'S';
	if (ls->mode & S_ISGID)
		chmod[6] = (chmod[6] == 'x') ? 's' : 'S';
	if (ls->mode & S_ISVTX)
		chmod[9] = (chmod[9] == 'x') ? 't' : 'T';
	chmod[10] = ft_acl(ls);
	chmod[11] = '\0';
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
	ls->flag = flag;
	return (ls);
}

int			init_struct(t_ls *ls, t_flag flag, char *path, int dostat)
{
	struct stat	file_stat;

	ls = pre_stat(ls, path, flag);
	if (!dostat)
		return (1);
	if (lstat(ls->path, &file_stat) < 0)
	{
		ft_printf("ls: cannot access \'%s\': %s\n",
					ls->name ? ls->name : ls->path, strerror(errno));
		free(path);
		return 0;
	}
	ls->mode = file_stat.st_mode;
	ls->chmod = ft_chmod(ls);
	ls->gname = get_group_name(file_stat.st_gid);
	ls->uname = get_user_name(file_stat.st_uid);
	ls->time = ls->flag.u ? file_stat.st_atimespec : file_stat.st_mtimespec;
	ls->tm = get_tm(ls->time);
	ls->nlink = file_stat.st_nlink;
	ls->link = lpath(ls->path, ls->mode);
	ls->size = file_stat.st_size;
	ls->block = file_stat.st_blocks;
	ls->rdev = file_stat.st_rdev;
	ls->next = NULL;
	return (1);
}
