/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:04:18 by user              #+#    #+#             */
/*   Updated: 2020/05/02 13:27:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <pwd.h>
#include <sys/xattr.h>
#include <stdlib.h>

# define FLAGS "adfgHlLRrtu"

# define NO_ARG		0
# define REQ_ARG	1
# define OPT_ARG	2

typedef struct	s_flag
{
	int			a_flag;
	int 		d_flag;
	int			f_flag;
	int 		g_flag;
	int 		h_capital;
	int 		l_flag;
	int 		l_capital;
	int 		r_capital;
	int 		r_flag;
	int			t_flag;
	int 		u_flag;
}				t_flag;

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
	char			chmod[10];		//права доступа
	char			*time;			//время DD MM
	char			*user_name;		//имя пользовтеля
	char			*group_name;	//имя групы
	int				byte_size;		//размер в байтах
	int				links;			//количество файлов внутри
    char            *name;			// имя файла или директории
	char			*path;			// полный путь до файла
    struct s_ls     *next;
}                   t_ls;

typedef struct		s_type
{
	int				flag;
	DIR				*dir;
	struct dirent	*entry;
	int				total;		//ls -l total
}					t_type;

typedef struct		s_dir
{
	char			*name;
	int				flag;
	t_ls			*ls;
	struct s_dir	*next;
}					t_dir;

static t_lopt 	g_lopt[] = {
		{"all", NO_ARG, NULL, 'a'},
		{"color", NO_ARG, NULL, 'c'},
		{"directory", NO_ARG, NULL, 'd'},
		{"dereference-command-line", NO_ARG, NULL, 'H'},
		{"dereference", NO_ARG, NULL, 'L'},
		{"recursive", NO_ARG, NULL, 'R'},
		{"reverse", NO_ARG, NULL, 'r'},
		{NULL,0,NULL,0}
};

void		print(char **buff, t_type type, char  *av);
char		**ft_ls_dir(char *av);
void		print_error(char *av);
t_ls		*init_struct(char *path, char *buff);
t_ls		*sort_list(t_ls *ls);
t_opt 		*set_start_opt_val(t_opt *opt);
int			ft_getopt(t_input inpt, t_opt *opt);
int 		ft_getopt_long(t_input data, t_opt **opt, t_lopt *lopt, int *lind);
//int 		get_num_of_array_index(t_input input);
void 		reset_flags(t_flag *flag);
void 		collect_flags(t_flag *flag, int ac, char ***av);

#endif
