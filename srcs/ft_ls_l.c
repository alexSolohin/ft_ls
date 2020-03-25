/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 16:03:27 by user              #+#    #+#             */
/*   Updated: 2020/03/25 18:24:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


void	ft_ls_l(t_ls *ls)
{
	// time_t time;
	char	*s;


	struct stat file_stat;
	if (stat(ls->name, &file_stat) < 0)
		exit(0);
	s = ctime(&file_stat.st_atimespec.tv_sec);
	printf("Time	%.16s\n", s);
	printf("Information for %s\n", ls->name);
	printf("---------------------------\n");
    printf("File Size: \t\t%lld bytes\n",file_stat.st_size);
    printf("Number of Links: \t%d\n",file_stat.st_nlink);
    printf("File inode: \t\t%lld\n",file_stat.st_ino);
	printf("Time \t\t%ld\n", file_stat.st_atime);

    printf("File Permissions: \t");
    printf( (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");
}
