/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:54:07 by rmaxima           #+#    #+#             */
/*   Updated: 2020/04/20 15:22:18 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


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
	char			*path;
	char			*name_dir;
    struct s_ls     *next;
}                   t_ls;

typedef struct		s_type
{
	int				flag;
	DIR				*dir;
	struct dirent	*entry;
	int				total;		//ls -l total
}					t_type;

void	print(t_ls *ls);
void	ft_ls_l(t_ls *ls);
void	print_error(char *av);
void	init_struct(t_ls *ls);

#endif
