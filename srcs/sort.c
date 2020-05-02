/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:49:48 by alex              #+#    #+#             */
/*   Updated: 2020/05/02 17:40:12 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// void        sort_time_create(char **buff, t_ls *ls)
// {


// }

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
	    while (j < n - i -1)
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
	//здесь будет сортировка по имени или в зависимости от ключа
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
	//здесь будет сортировка по имени или в зависимости от ключа
}


