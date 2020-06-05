/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 12:54:07 by user              #+#    #+#             */
/*   Updated: 2020/06/05 15:00:38 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_strmode(mode_t mode, char *buf)
{
	const char		chars[] = "rwxrwxrwx";
	int				i;

	i = 0;
	while (i < 9)
	{
		buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
		i++;
	}
	buf[9] = '\0';
}

char				*ft_chmod(t_ls *ls)
{
	char			chmod[12];

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

t_ls				*pre_stat(t_ls *ls, char *path, t_flag flag)
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

int					init_struct(t_ls *ls, t_flag flag, char *path, int dostat)
{
	struct stat		file_stat;

	ls = pre_stat(ls, path, flag);
	if (!dostat)
		return (1);
	if (lstat(ls->path, &file_stat) < 0)
	{
		ft_printf("ls: cannot access \'%s\': %s\n",
					ls->name ? ls->name : ls->path, strerror(errno));
		free(path);
		return (0);
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
