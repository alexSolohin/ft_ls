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
# include <sys/types.h>
# include <grp.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <pwd.h>
# include <time.h>
# include <sys/xattr.h>
# include <stdlib.h>

# define FLAGS			"adfglRrtu"

# define CURR_DIR		"."
# define PARENT_DIR		".."
#define MAX_PATH		255
# define NO_ARG			0
# define REQ_ARG		1
# define OPT_ARG		2
# define BTW_COL        7

typedef struct timespec	t_time;
typedef struct passwd	t_user;
typedef struct group	t_group;


typedef struct			s_flag
{
	int					a;
	int 				d;
	int					f;
	int 				g;
	int 				l;
	int 				r_cap;
	int 				r;
	int					t;
	int 				u;
}						t_flag;

typedef struct	s_opt
{
	char		*optarg;
	int 		optind;
	int			optchar;
	char 		*optdecl;
	char 		*optopt;
}				t_opt;

typedef struct	s_lopt
{
	const char *name;
	int 		hasarg;
	int			*flag;
	int 		val;
}				t_lopt;

typedef struct s_input
{
	int			ac;
	char		**av;
}				t_input;

typedef struct      s_ls
{
	t_flag			flag;			//флаг
	t_time			time;			//время DD MM
	uid_t 			uid;			//id пользовтеля
	gid_t 			gid;			//id групы
	dev_t			rdev;			//номер устройства
	mode_t			mode;
	int64_t  		block;			//кол-во выделенных блоков
	char			chmod[12];		//права доступа
	long			size;			//размер в байтах
	unsigned short	nlink;			//количество файлов внутри
    char            *name;			// имя файла или директории
    char			*path;
    struct s_ls     *next;
}                   t_ls;

typedef struct		s_dir
{
	struct dirent	*dirent;
	DIR				*dp;
}					t_dir;

typedef struct      s_columns
{
    int             max_len_list;
    int             max_len;
    int             columns;
    int             word_in_column;
}                   t_columns;

static t_lopt 	g_lopt[] = {
		{"all", NO_ARG, NULL, 'a'},
		{"color", NO_ARG, NULL, 'c'},
		{"directory", NO_ARG, NULL, 'd'},
		{"recursive", NO_ARG, NULL, 'R'},
		{"reverse", NO_ARG, NULL, 'r'},
		{NULL,0,NULL,0}
};

int			entry_compare(t_ls *a, t_ls *b);
void		merge_sort(t_ls **list_to_sort);
void		print(t_ls *ls);
void 		ft_ls_dir(char *dir_path, t_flag f);
void		print_error(char *av);
int			init_struct(t_ls *ls, t_flag flag, char *path, int dostat);
t_ls		*sort_list(t_ls *ls);
char        **create_arr(t_ls *ls, int  max_len_list);
t_opt 		*set_start_opt_val(t_opt *opt);
int			ft_getopt(t_input inpt, t_opt *opt);
int 		ft_getopt_long(t_input data, t_opt **opt, t_lopt *lopt, int *lind);
void 		reset_flags(t_flag *flag);
void 		collect_flags(t_flag *flag, int *ac, char ***av);
void		print_output(t_ls *ls);
char		*ft_chmod(t_ls *ls);
void 		ft_ls(t_ls *ls, int list_dir, int show_dir);
void		add_ls_node(t_ls *entry, t_ls **ls);
void 		free_list(t_ls *ls);
void		ft_ls_internal(t_ls *ls, int show_dir);
char		*get_user_name(uid_t user_id);
char 		*get_group_name(gid_t group_id);
char		*get_time(t_time t);
int64_t		total_blk(t_ls *ls);

#endif
