/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:55:26 by alex              #+#    #+#             */
/*   Updated: 2020/04/08 13:14:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>



int		sort_alphabet(char *a, char *b)
{
	int i;

	i = 0;
	while (b[i])
	{
		if (a[i] > b[i])
			return (1);
		else
			return (0);
		i++;
	}
	return (1);
}

t_ls	*sort_list(t_ls *ls)
{
	char	*tmp;
	int		type;
	t_ls	*ptr;

	ptr = ls;
	while (ls->next != NULL && ls->next->name != NULL)
	{
		if (sort_alphabet(ls->name, ls->next->name))
		{
			tmp = malloc(sizeof(char) * 255);
			tmp = ls->name;
			type = ls->flag;
			ls->name = ls->next->name;
			ls->next->name = tmp;
			ls->flag = ls->next->flag;
			ls->next->flag = type;
			ls = ptr;
		}
		else
			ls = ls->next;
	}
	ls = ptr;
	return (ls);
}

void	ft_ls_a(t_ls *ls)
{
	if ((ls->name[0] == '.' && ls->name[1] == '\0') || (ls->name[0] == '.' && ls->name[1] == '.'))
    {
        ft_putstr(ls->name);
		ft_putstr("        ");
        // ls = ls->next;
	}
}

void	ft_ls_type(t_type *type, t_ls *ls)
{
	if (type->flag == 1)
	{
		if (ls->name[0] == '.')
			ls = ls->next;
		else
			ft_ls_l(ls);
	}
	else if (type->flag == 2)
		printf("2");
	else if (type->flag == 3)
		ft_ls_a(ls);
	else if (type->flag == 4)
		printf("4");
	else if (type->flag == 5)
		printf("5");


}



void	ft_ls_dir(char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	t_ls			*ls;

	dir = opendir(".");

	if (!(ls = malloc(sizeof(t_ls))))
		exit(0);
	if (!dir)
		print_error(av);
	while ((entry = readdir(dir)) != NULL)
	{
		ls->name = entry->d_name;
		init_struct(ls);
		int i = 0;
		while (i < 10)
		{
			printf("%c", ls->chmod[i]);
			i++;
		}
		printf("\t%d", ls->links);
		printf("\t%s\t%s\t%d", ls->user_name, ls->group_name, ls->byte_size);
		printf("\t%.16s %s\n", ls->time, ls->name);
	}
	closedir(dir);
}

int		ft_ls(t_type *type, char *av)
{
	type->flag = 0;
	if (ft_strequ(av, "-l"))
		type->flag = 1;
	else if (ft_strequ(av, "-R"))
		type->flag = 2;
	else if (ft_strequ(av, "-a"))
		type->flag = 3;
	else if (ft_strequ(av, "-r"))
		type->flag = 4;
	else if (ft_strequ(av, "-t"))
		type->flag = 5;
	else
		return (0);
	return (1);
}


//stat разобрать, там найдем нужные расширения
int     main(int ac, char **av)
{
	t_ls	*ls;

	av = 0;
	if (!(ls = malloc(sizeof(t_ls))))
		exit(0);
	if (ac == 1)
		ft_ls_dir(".");


}
