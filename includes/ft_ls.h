/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:54:07 by rmaxima           #+#    #+#             */
/*   Updated: 2020/04/18 15:39:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"



typedef struct      s_ls
{
    int             flag;			//флаг
	char			chmod[10];		//права доступа
	char			*time;			//время DD MM
	char			*user_name;		//имя пользовтеля
	char			*group_name;	//имя групы
	int				byte_size;		//размер в байтах
	int				links;			//количество файлов внутри
    char            *name;			// имя файла или директории
	char			*name_dir;
    struct s_ls     *next;
}                   t_ls;

typedef struct		s_type
{
	int				flag;
}					t_type;

void	print(t_ls *ls);
void	ft_ls_l(t_ls *ls);
void	print_error(char *av);
void	init_struct(char *str, t_ls *ls);

#endif
