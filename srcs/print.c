/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:49:34 by user              #+#    #+#             */
/*   Updated: 2020/03/22 19:02:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		max_size_name(t_ls *ls)
{
	t_ls	*ptr;
	int		size;
	char	*tmp;

	ptr = ls;
	size = 0;
	while (ls->next != NULL && ls->next->name != NULL)
	{
		if (ft_strlen(ls->name) > ft_strlen(ls->next->name))
		{
			tmp = malloc(sizeof(char) * 255);
			tmp = ls->name;
			ls->name = ls->next->name;
			ls->next->name = tmp;
			ls = ptr;
		}
		else
			ls = ls->next;
	}
	return (ft_strlen(ls->name));
}

void	print(t_ls *ls)
{
	int 	len_name;
	int 	max_size;
	int		list_len;
	int		max_len;
	t_ls 	*ptr;
	char	str[255][1024];

	max_size = 16;
	list_len = 0;
	ptr = ls;
	max_len = max_size_name(ls);
	ls = sort_list(ls);
	while (ptr->next != NULL)
	{
		list_len++;
		ptr = ptr->next;
	}

	int i;
	int j;

	i = 0;
	while (ls->next != NULL)
	{
		j = 0;
		len_name = ft_strlen(ls->name);
		while (j <= max_len + 4)   //закончил здесь, нужно сделать вывод в консоль как в ls идея закинуть в массив а потом уже выводить
		{
			if (len_name-- > 0)
				str[i][j] = ls->name[j];
			else
				str[i][j] = ' ';
			j++;
		}
		printf("%s\n", str[i]);
		ls = ls->next;
		i++;
	}
}
// 	while (ls->next->next->next != NULL && ls->next->next->next->name != NULL)
// 	{
// 		len_name = ft_strlen(ls->name);
// 		if (len_name <= max_len)
// 		{
// 			ft_putstr(ls->name);
// 			while ((max_len + 4) - len_name)
// 			{
// 				ft_putstr(" ");
// 				len_name++;
// 			}
// 			len_name = ft_strlen(ls->next->next->name);
// 			ft_putstr(ls->next->next->name);
// 			while ((max_len + 4) - len_name)
// 			{
// 				ft_putstr(" ");
// 				len_name++;
// 			}
// 			ft_putstr("\n");
// 			ft_putstr(ls->next->name);
// 			len_name = ft_strlen(ls->next->name);
// 			while ((max_len + 4) - len_name)
// 			{
// 				ft_putstr(" ");
// 				len_name++;
// 			}
// 			ls = ls->next->next->next;
// 		}
	// }
// }
