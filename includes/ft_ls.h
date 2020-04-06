/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:54:07 by rmaxima           #+#    #+#             */
/*   Updated: 2020/04/06 15:08:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"



typedef struct      s_ls
{
    int             flag;			//флаг
	char			chmod[10];		//права доступа
	char			time[17];		//время DD MM
	char			*user_name;		//имя пользовтеля
	char			*group_name;	//имя групы
	int				byte_size;		//размер в байтах
	int				links;			//количество файлов внутри
    char            *name;			// имя файла или директории
    struct s_ls     *next;
}                   t_ls;

typedef struct		s_type
{
	int				flag;
}					t_type;

typedef struct		s_dir
{
	char			*name;
	int				flag;
	t_ls			*ls;
	struct s_dir	*next;
}					t_dir;

void	print(t_ls *ls);
void	ft_ls_l(t_ls *ls);
void	print_error(char *av);
t_ls	*sort_list(t_ls *ls);

#endif
