/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:54:07 by rmaxima           #+#    #+#             */
/*   Updated: 2020/03/25 18:11:19 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"



typedef struct      s_ls
{
    int             flag;
    int             flag_end;
    int             type;
	char			chmod[12];
    char            *name;
    struct s_ls     *next;
}                   t_ls;

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

void	print(t_ls *ls);
void	ft_ls_l(t_ls *ls);
void	print_error(char *av);
t_ls	*sort_list(t_ls *ls);

#endif
