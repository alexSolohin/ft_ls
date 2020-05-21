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

    len = ft_strlen(ptr);
    while (len < max_len)
    {
        printf(" ");
        len++;
    }
}

void    name_ls(char **ptr, int word_in_column, int columns, int max_len)
{
    int i;
    int k;

    i = 0;
    while(i < word_in_column)
    {
        printf("%s", ptr[i]);
        write_space(ptr[i], max_len);
        k = 1;
        while (k < columns)
        {
            if (ptr[i + word_in_column * k] != '\0')
            {
                printf("%s", ptr[i + word_in_column * k]);
                write_space(ptr[i + word_in_column * k], max_len);
            }
            k++;
        }
        i++;
        printf("\n");

    }
}

char        **create_arr(t_ls *ls)
{
    char **ptr;

    ptr = malloc(sizeof(char*));
    int i = 0;
    while (ls)
    {
        ptr[i] = ls->name;
        ls = ls->next;
        i++;
    }
    ptr[i] = NULL;
    return (ptr);
}

void        print(t_ls *ls)
{
    struct      winsize  window;
    int         max_len_list;
    int      max_len;
    int      columns;
    int         word_in_column;
    char        **ptr;

    ptr = NULL;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
    max_len = max_size_name(ls) + 7;
    max_len_list = max_size_list(ls);
    columns = window.ws_col / max_len;
    if (max_len_list % columns != 0)
        word_in_column = max_len_list / columns + 1;
    else
        word_in_column = max_len_list / columns;
    ptr = create_arr(ls);
    name_ls(ptr, word_in_column, columns, max_len);
}


