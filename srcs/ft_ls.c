/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:55:26 by alex              #+#    #+#             */
/*   Updated: 2020/03/22 02:14:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

void	print_error(char *av)
{
	ft_putstr("ls: ");
	ft_putstr(av);
	ft_putstr(": No such file or directory\n");
	exit(0);
}

t_ls	*sort_name(t_ls *ls)
{
	char	*tmp;
	int		type;
	t_ls	*ptr;
	char	a;
	char	b;


	ptr = ls;
	a = ls->name[0];
	b = ls->next->name[0];
	if (a < b)
	{
		tmp = malloc(sizeof(char) * 255);
		tmp = ls->name;
		type = ls->type;
		ls->name = ls->next->name;
		ls->next->name = tmp;
		ls->type = ls->next->type;
		ls->next->type = type;
		ls = ptr;
	}
	return(ls);
}

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
			type = ls->type;
			ls->name = ls->next->name;
			ls->next->name = tmp;
			ls->type = ls->next->type;
			ls->next->type = type;
			ls = ptr;
		}
		else
			ls = ls->next;
	}
	ls = ptr;
	return (ls);
}

void	ft_ls_zero(t_ls *ls, char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	t_ls			*ptr;

	dir = opendir(av);
	if (!dir)
		print_error(av);
	while ((entry = readdir(dir)) != NULL)
	{
		ptr = malloc(sizeof(t_ls));
		ptr->name = entry->d_name;
		ptr->type = entry->d_type;
		ptr->next = ls;
		ls = ptr;
		if (ls->name[0] == '.')
			ls = ls->next;
	}
	ls = sort_list(ls);
	while (ls->next != NULL)
	{
		ft_putstr(ls->name);
		if (ls->next->name != NULL)
			ft_putstr("        ");
		ls = ls->next;
	}
	closedir(dir);
}

void	ft_ls_a(t_ls *ls, char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	t_ls			*ptr;

	av = 0;
	dir = opendir(".");
	if (!dir)
		print_error(".");
	while ((entry = readdir(dir)) != NULL)
	{
		ptr = malloc(sizeof(t_ls));
		ptr->name = entry->d_name;
		ptr->type = entry->d_type;
		ptr->next = ls;
		ls = ptr;
		if ((ls->name[0] == '.' && ls->name[1] == '\0') || (ls->name[0] == '.' && ls->name[1] == '.'))
        {
            ft_putstr(ls->name);
			ft_putstr("        ");
            ls = ls->next;
        }
	}
	ls = sort_list(ls);
	while (ls->next != NULL)
	{
		ft_putstr(ls->name);
		if (ls->next->name != NULL)
			ft_putstr("        ");
		ls = ls->next;
	}
	closedir(dir);
}

void	ft_ls(t_ls *ls, char *av)
{
	// if (av[0] == '.')
	// 	ft_ls_zero(ls, av);
	if (ft_strequ(av, "-l"))
		ls->flag = 1;
	else if (ft_strequ(av, "-R"))
		ls->flag = 2;
	else if (ft_strequ(av, "-a"))
		ft_ls_a(ls, av);
	else if (ft_strequ(av, "-r"))
		ls->flag = 4;
	else if (ft_strequ(av, "-t"))
		ls->flag = 5;
	else
		ft_ls_zero(ls, av);

}


int     main(int ac, char **av)
{
	t_ls			*ls;

	ls = malloc(sizeof(t_ls));
	if (ac == 1)
	{
		ft_ls(ls, ".");
	}
	else if (ac >= 2)
	{
		ft_ls(ls, av[1]);
	}

}
