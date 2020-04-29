/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:54:07 by rmaxima           #+#    #+#             */
/*   Updated: 2020/03/26 17:23:29 by user             ###   ########.fr       */
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

# define FLAGS "adfglRrtu"

# define NO_ARG		0
# define REQ_ARG	1
# define OPT_ARG	2

typedef struct	s_flag
{
	int			a_flag;
	int 		d_flag;
	int			f_flag;
	int 		g_flag;
	int 		l_flag;
	int 		rec_flag;
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

typedef struct	s_ls
{
    t_flag		flag;
    int			flag_end;
    int			type;
	char		chmod[10];
	char		time[17];
	char		*user_name;
	char		*group_name;
	int			byte_size;
	int			links;
    char		*name;
    struct s_ls	*next;
}				t_ls;

typedef struct		s_type
{
	int				flag;
}					t_type;

typedef struct		s_dir
{
	int				flag;
	t_ls			*ls;
	struct s_dir	*next;
}					t_dir;

static t_lopt 	g_lopt[] = {
		{"all", NO_ARG, NULL, 'a'},
		{"color", NO_ARG, NULL, 'c'},
		{"directory", NO_ARG, NULL, 'd'},
		{"recursive", NO_ARG, NULL, 'R'},
		{"reverse", NO_ARG, NULL, 'r'},
		{NULL,0,NULL,0}
};

void		print(t_ls *ls);
void		ft_ls_dir(char *av);
void		ft_ls_l(t_ls *ls);
void		print_error(char *av);
t_ls		*sort_list(t_ls *ls);
t_opt 		*set_start_opt_val(t_opt *opt);
int			ft_getopt(t_input inpt, t_opt *opt);
int 		ft_getopt_long(t_input data, t_opt **opt, t_lopt *lopt, int *lind);
//int 		get_num_of_array_index(t_input input);
void 		reset_flags(t_flag *flag);
void 		collect_flags(t_flag *flag, int ac, char ***av);

#endif
