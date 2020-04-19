/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 16:03:27 by user              #+#    #+#             */
/*   Updated: 2020/04/04 17:58:09 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void	ft_ls_l(t_ls *ls)
{
	struct passwd 	*pws;
	struct stat 	file_stat;
	char			*s;
	struct group	*group;

	if ((group = getgrgid(getgid())) != NULL)
    	ls->group_name = group->gr_name;
	if ((pws = getpwuid(geteuid())) != NULL)
		ls->user_name = pws->pw_name;
	if (stat(ls->name, &file_stat) < 0)
		exit(0);
	s = ctime(&file_stat.st_atimespec.tv_sec);
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

	ls->links = file_stat.st_nlink;
	ls->byte_size = file_stat.st_size;

	int i = 0;
	while (i < 10)
	{
		printf("%c", ls->chmod[i]);
		i++;
	}
	printf("\t%d", ls->links);
	printf("\t%s\t%s\t%d", ls->user_name, ls->group_name, ls->byte_size);
	printf("\t%.16s %s\n", s, ls->name);

	// printf("Time	%.16s\n", s);
	// printf("Information for %s\n", ls->name);
	// printf("---------------------------\n");
    // printf("File Size: \t\t%lld bytes\n",file_stat.st_size);
    // printf("Number of Links: \t%d\n",file_stat.st_nlink);
    // printf("File inode: \t\t%lld\n",file_stat.st_ino);
	// printf("Time \t\t%ld\n", file_stat.st_atime);

    // printf("File Permissions: \t");
    // printf( (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    // printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
    // printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
    // printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
    // printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
    // printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
    // printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
    // printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
    // printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
    // printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");
}
