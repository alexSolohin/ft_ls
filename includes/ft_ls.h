/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:04:18 by user              #+#    #+#             */
/*   Updated: 2020/05/01 12:57:38 by alex             ###   ########.fr       */
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

void	ft_ls_l(t_ls *ls);
int		size_buff(char *av);
void	print_error(char *av);
t_ls	*init_struct(char *path, char *av);

#endif
