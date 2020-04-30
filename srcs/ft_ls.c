/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:27:13 by user              #+#    #+#             */
/*   Updated: 2020/04/29 20:58:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>


//	parser to file
//	opendir(../dir)
//		while (entry = readdir())

int		sort_alphabet(char *a, char *b)
{
	int i;

	i = 0;
	if (a[i] == '.')
		return (1);
	while (b[i])
	{
		if (a[i] > b[i])
			return (1);
		i++;
	}
	return (0);
}

t_ls	*sort_list(t_ls *ls)
{
//	char	*tmp;
	int		type_a;
	t_ls	*ptr;
	t_ls	*tmp;

	ptr = NULL;
	type_a = 0;
	while (ls != NULL)
	{
		// if (ls->name[0] == '.' && type_a != 1)
		tmp = ls;
		ls = ls->next;
		if (ptr == NULL || sort_alphabet(tmp->name, ptr->name))
		{
			tmp->next = ptr;
			ptr = tmp;
		}
		else
		{
			t_ls *current = ptr;
			while (current->next != NULL && !sort_alphabet(tmp->name, current->next->name))
			{
				current = current->next;
			}
			tmp->next = current->next;
			current->next = tmp;
		}
	}
	return (ptr);
}

void	ft_ls_dir(t_ls **ls, char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	t_ls			*ptr;
	int				total;


	dir = opendir(av);
	if (!dir)
		exit(0);

	total = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		ptr = malloc(sizeof(t_ls));
		init_struct(ptr, av);
		ptr->next = (*ls);
		(*ls) = ptr;
	}
	// ls = sort_list(ls);

	closedir(dir);
}

int     main(int ac, char **av)
{
	t_ls **ls;

	ls = malloc(sizeof(t_ls*));
	ac = 0;
	ft_ls_dir(ls, av[1]);

	t_ls *ptr;
	ptr = *ls;
	while (ptr->next)
	{
		int i = 0;
		while (i < 10)
			printf("%c", ptr->chmod[i++]);
		printf(" %d %s %s", ptr->links, ptr->group_name, ptr->user_name);
		printf(" %d %.16s %s\n", ptr->byte_size, ptr->time, ptr->name);
		ptr = ptr->next;
	}
}
