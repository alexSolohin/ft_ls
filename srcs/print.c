/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:49:34 by user              #+#    #+#             */
/*   Updated: 2020/03/25 17:20:07 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <sys/ioctl.h>

double		max_size_name(t_ls *ls)
{
    double size;

	size = 0;
	while (ls->next != NULL)
	{
		if ((ft_strlen(ls->name) > ft_strlen(ls->next->name)) && size < ft_strlen((ls->name)))
			size = ft_strlen(ls->name);
		ls = ls->next;
	}
	return (size);
}

int     max_size_list(t_ls *ls)
{
    int size;

    size = 0;
    while (ls)
    {
        size++;
        ls = ls->next;
    }
    return (size);
}

void    write_space(char *ptr, int max_len)
{
    int len;

    if (ptr == NULL)
        return ;
    len = ft_strlen(ptr);
    while (len < max_len)
    {
        printf(" ");
        len++;
    }
}

void    name_ls(char **ptr, t_columns columns)
{
    int i;
    int k;

    i = 0;
    while(i < columns.word_in_column)
    {
        printf("%s", ptr[i]);
        write_space(ptr[i], columns.max_len);
        k = 1;
        while (k < columns.columns)
        {
            if ((i + columns.word_in_column * k) < columns.max_len_list)
            {
                printf("%s", ptr[i + columns.word_in_column * k]);
                write_space(ptr[i + columns.word_in_column * k], columns.max_len);
            }
            k++;
        }
        i++;
        printf("\n");
    }
}

void        print(t_ls *ls)
{
    struct      winsize  window;
    t_columns   columns;
    char        **ptr;

    ptr = NULL;
    ioctl(0, TIOCGWINSZ, &window);
    columns.max_len = max_size_name(ls) + BTW_COL;
    columns.max_len_list = max_size_list(ls);
    columns.columns = window.ws_col / columns.max_len;
//    columns = 100 / max_len;
    if (columns.columns == 0)
        columns.word_in_column = columns.max_len_list;
    else if (columns.max_len_list % columns.columns != 0)
        columns.word_in_column = columns.max_len_list / columns.columns + 1;
    else
        columns.word_in_column = columns.max_len_list / columns.columns;
    ptr = create_arr(ls, columns.max_len_list);
    name_ls(ptr, columns);
    free(ptr);
    printf("\n");
}


