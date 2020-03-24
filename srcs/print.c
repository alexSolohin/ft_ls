/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:49:34 by user              #+#    #+#             */
/*   Updated: 2020/03/24 16:51:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <sys/ioctl.h>

void	sort_arr(char str[][1024], int size_arr, int max_len)
{
	int i;
	int j;
	int k;
	char ptr[255][1024];

	i = 0;
	k = 0;
	max_len = 0;
	while (i < size_arr / 2  + 1)
	{
		j = 0;
		while (str[i][j])
		{
			ptr[k][j] = str[i][j];
			if (size_arr / 2 + i != size_arr / 2)
				ptr[k + 1][j] = str[size_arr / 2 + i][j];
			else
			{
				ptr[k + 1][j] = str[size_arr / 2 + 1][j];
				//закончил здесь
				// необходимо закинуть в массив строки 0 - size_arr / 2
			}
			j++;
		}
		ptr[k][j] = '\0';
		// if (i <= size_arr / 2)
		// 	printf("%s", str[i]);
		// printf("%s\n", str[size_arr/2 + i]);
		printf("%s %s\n", ptr[i], ptr[i + 1]);
		// else
		// {
		// 		if (i < size_arr / 2 + 1)
		// 			printf("%s", str[i]);
		// 		if ((size_arr / 2 + i) != (size_arr / 2 + 1))
		// 			printf("%s\n", str[size_arr / 2 + i]);
		// }
		i++;
		k++;
	}
}

void	print_columns(char str[][1024], struct winsize window, int max_len, int size_arr)
{
	int i;

	i = 0;
	if (window.ws_col < (max_len + 3) * 2)
		while (i < size_arr)
			printf("%s\n", str[i++]);
	else if (window.ws_col >= (max_len + 3) * 2)
	{
			sort_arr(str, size_arr, max_len);
	}

}

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
	struct winsize  window;

	int 	len_name;
	int 	max_size;
	int		list_len;
	int		max_len;
	t_ls 	*ptr;
	char	str[255][1024];


	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
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
		while (j <= max_len + 3)   //закончил здесь, нужно сделать вывод в консоль как в ls идея закинуть в массив а потом уже выводить
		{
			if (len_name-- > 0)
				str[i][j] = ls->name[j];
			else
				str[i][j] = ' ';
			j++;
		}
		// printf("%send\n", str[i]);
		ls = ls->next;
		i++;
	}
	// str[i][0] = '\0';
	print_columns(str, window, max_len, i);
	// printf("kibes %d\n", window.ws_row);
	printf("max len %d", max_len);
	printf("columns %d\n", window.ws_col);
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
