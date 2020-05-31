/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:04:18 by user              #+#    #+#             */
/*   Updated: 2020/04/24 15:04:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
#include "ft_getopt.h"
# include <sys/types.h>
# include <grp.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <pwd.h>
# include <sys/xattr.h>
# include <stdlib.h>
# include <errno.h>
# include <time.h>

# define CURR_DIR		"."
# define MAX_PATH		255

typedef struct timespec	t_time;
typedef struct passwd	t_user;
typedef struct group	t_group;

typedef struct      s_ls
{
	char            *name;			// имя файла или директории
	char			*path;
	char			*chmod;			//права доступа
	unsigned short	nlink;			//количество файлов внутри
	char 			*uname;			//имя пользователя
	char			*gname;			//имя группы
	long			size;			//размер в байтах
	char 			*tm;			//форматируемая дата
	char 			*link;			// файл на который указывает символьная сылка
	char 			*color;			//цвет файла
	t_flag			flag;			//флаг
	t_time			time;			//время DD MM
	dev_t			rdev;			//номер устройства
	mode_t			mode;
	int64_t  		block;			//кол-во выделенных блоков
    struct s_ls     *next;
}                   t_ls;

typedef struct 		s_print
{
	int 			max_mode;
	int 			max_name;
	int 			max_nlink;
	int 			max_size;
}					t_print;

typedef struct		s_dir
{
	struct dirent	*dirent;
	DIR				*dp;
}					t_dir;

int			entry_compare(t_ls *a, t_ls *b);
void		merge_sort(t_ls **list_to_sort);
void		print(t_ls *ls);
void 		ft_ls_dir(char *dir_path, t_flag f, int show_dir);
void		print_error(char *av);
int			init_struct(t_ls *ls, t_flag flag, char *path, int dostat);
t_ls		*sort_list(t_ls *ls);
void 		reset_flags(t_flag *flag);
void 		collect_flags(t_flag *flag, int *ac, char ***av);
void		print_output(t_ls *ls);
t_print		print_utils(t_ls *ls);
char		*ft_chmod(mode_t mode);
void 		ft_ls(t_ls *ls, int list_dir, int show_dir);
void		add_ls_node(t_ls *entry, t_ls **ls);
void 		free_list(t_ls *ls);
char		*get_user_name(uid_t user_id);
char 		*get_group_name(gid_t group_id);
char		*get_tm(t_time t);
int64_t		total_blk(t_ls *ls);
unsigned 	mjr(t_ls *ls);
unsigned	mnr(t_ls *ls);
char 		*lpath(char *linkname, mode_t mode);
void 		set_color(mode_t mode, int do_color);

#endif
