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

# define FLAGS "adflRru"

# define NO_ARG		0
# define REQ_ARG	1
# define OPT_ARG	2

typedef struct	s_opt
{
	char		*optarg;
	int 		optind;
	int			optchar;
	char 		*optdecl;
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
    int			flag;
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

void		print(t_ls *ls);
void		ft_ls_l(t_ls *ls);
void		print_error(char *av);
t_ls		*sort_list(t_ls *ls);
t_opt 		*set_start_opt_val(t_opt *opt);
int			ft_getopt(t_input inpt, t_opt *opt, char *optstr);
int 		ft_getopt_long(t_input data, t_opt *opt, t_lopt *lopt, int *longind);

#endif
