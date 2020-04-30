/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:26:33 by user              #+#    #+#             */
/*   Updated: 2020/04/30 14:48:54 by user             ###   ########.fr       */
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

void	ft_chmod(struct stat file_stat, t_ls *ls)
{
	ls->chmod[0] = (S_ISDIR(file_stat.st_mode)) ? 'd' : '-';
	ls->chmod[1] = (file_stat.st_mode & S_IRUSR) ? 'r' : '-';
	ls->chmod[2] = (file_stat.st_mode & S_IWUSR) ? 'w' : '-';
	ls->chmod[3] = (file_stat.st_mode & S_IXUSR) ? 'x' : '-';
	ls->chmod[4] = (file_stat.st_mode & S_IRGRP) ? 'r' : '-';
	ls->chmod[5] = (file_stat.st_mode & S_IWGRP) ? 'w' : '-';
	ls->chmod[6] = (file_stat.st_mode & S_IXGRP) ? 'x' : '-';
	ls->chmod[7] = (file_stat.st_mode & S_IROTH) ? 'r' : '-';
	ls->chmod[8] = (file_stat.st_mode & S_IWOTH) ? 'w' : '-';
	ls->chmod[9] = (file_stat.st_mode & S_IXOTH) ? 'x' : '-';
}

t_ls	*init_struct(char *path, char *buff)
{
	struct passwd 	*pws;
	struct stat 	file_stat;
	struct group	*group;
	t_ls			*ls;


	ls = malloc(sizeof(t_ls));
	ls->name = ft_strdup(buff);
	if ((group = getgrgid(getgid())) != NULL)
		ls->group_name = group->gr_name;
	if ((pws = getpwuid(geteuid())) != NULL)
		ls->user_name = pws->pw_name;
	if (ft_strequ(buff, ".") || ft_strequ(buff, ".."))
	{
		if (stat(buff, &file_stat) < 0)
			exit(0);
	}
	else
	{
		if (stat(path, &file_stat) < 0)
			exit(0);
	}
	ls->time = ctime(&file_stat.st_atimespec.tv_sec);
	ls->links = file_stat.st_nlink;
	ls->byte_size = file_stat.st_size;
	ft_chmod(file_stat, ls);
	return (ls);
}
