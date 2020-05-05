/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:49:48 by alex              #+#    #+#             */
/*   Updated: 2020/05/03 13:11:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void        rev_data(t_ls *ptr, t_ls *ls)
{
    t_ls tmp;

    tmp.time_nsec = ls->time_nsec;
    tmp.time = ls->time;
    tmp.byte_size = ls->byte_size;
    tmp.flag = ls->flag;
    tmp.st_block = ls->st_block;
    int i = 0;
	while (i < 10)
    {
        tmp.chmod[i] = ls->chmod[i];
        i++;
    }
    tmp.links = ls->links;
    tmp.path = ls->path;
    tmp.group_name = ls->group_name;
    tmp.name = ls->name;
	ls->time_nsec = ptr->time_nsec;
    ls->time = ptr->time;
    ls->byte_size = ptr->byte_size;
    ls->flag = ptr->flag;
    ls->st_block = ptr->st_block;
    i = 0;
	while (i < 10)
    {
        ls->chmod[i] = ptr->chmod[i];
        i++;
    }
    ls->links = ptr->links;
    ls->path = ptr->path;
    ls->group_name = ptr->group_name;
    ls->name = ptr->name;
	ptr->time_nsec = tmp.time_nsec;
    ptr->time = tmp.time;
    ptr->byte_size = tmp.byte_size;
    ptr->flag = tmp.flag;
    ptr->st_block = tmp.st_block;
    i = 0;
	while (i < 10)
    {
        ptr->chmod[i] = tmp.chmod[i];
        i++;
    }
    ptr->links = tmp.links;
    ptr->path = tmp.path;
    ptr->group_name = tmp.group_name;
    ptr->name = tmp.name;
}

void        sort_equaly(t_ls *ls)
{
    t_ls *ptr;

    ptr = NULL;
    if (ls != NULL)
    {
        while (ls->next != NULL)
        {
            ptr = ls->next;
            while (ptr != NULL)
            {
                if (ptr->time_nsec == ls->time_nsec)
                {
                    if (ft_strcmp(ls->name, ptr->name) > 0)
                        rev_data(ptr, ls);
                }
                ptr = ptr->next;
            }
            ls = ls->next;
        }
    }
}

void        sort_time_create(t_ls *ls)
{
    t_ls *ptr;

    ptr = NULL;
    if (ls != NULL)
    {
        while (ls->next != NULL)
        {
            ptr = ls->next;
            while (ptr != NULL)
            {
                if (ptr->time_nsec > ls->time_nsec)
                {
                    rev_data(ptr, ls);
                }
                if (ptr->time_nsec == ls->time_nsec)
                {
                     /*
                      * лексикографический порядок
                      * доработать функцию
                     */
                    if (ft_strcmp(ls->name, ptr->name) > 0)
                        rev_data(ptr, ls);
                }
                ptr = ptr->next;
            }
            ls = ls->next;
        }
    }

}

void	sort_name_rev(char **buff)
{
	size_t  i;
	size_t  j;
	size_t  n;
	char    *ptr;

	n = 0;
	while(buff[n])
	    n++;
	i = 0;
	while (i < n)
	{
	    j = 0;
	    while (j < n - i - 1)
		{
	        if (ft_strcmp(buff[j], buff[j + 1]) > 0)
	        {
	            ptr = buff[j];
	            buff[j] = buff[j + 1];
	            buff[j + 1] = ptr;
            }
	        j++;
        }
	    i++;
    }
//    i = 0;
//	while(buff[i])
//    {
//        printf("%s\n", buff[i++]);
//    }
}

void	sort_name(char **buff)
{

	size_t  i;
	size_t  j;
	size_t  n;
	char    *ptr;

	n = 0;
	while(buff[n])
	    n++;
	i = 0;
	while (i < n)
	{
	    j = 0;
	    while (j < n - i -1)
		{
	        if (ft_strcmp(buff[j], buff[j + 1]) < 0)
	        {
	            ptr = buff[j];
	            buff[j] = buff[j + 1];
	            buff[j + 1] = ptr;
            }
	        j++;
        }
	    i++;
    }
//    i = 0;
//	while(buff[i])
//    {
//        printf("%s\n", buff[i++]);
//    }

}


