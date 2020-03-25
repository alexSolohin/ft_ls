/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:55:26 by alex              #+#    #+#             */
/*   Updated: 2020/03/25 18:11:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>

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

// void	ft_ls_a(t_ls *ls, char *av)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;
// 	t_ls			*ptr;

// 	av = 0;
// 	dir = opendir(".");
// 	if (!dir)
// 		print_error(".");
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		ptr = malloc(sizeof(t_ls));
// 		ptr->name = entry->d_name;
// 		ptr->type = entry->d_type;
// 		ptr->next = ls;
// 		ls = ptr;
// 		if ((ls->name[0] == '.' && ls->name[1] == '\0') || (ls->name[0] == '.' && ls->name[1] == '.'))
//         {
//             ft_putstr(ls->name);
// 			ft_putstr("        ");
//             ls = ls->next;
//         }
// 	}
// 	ls = sort_list(ls);
// 	while (ls->next != NULL)
// 	{
// 		ft_putstr(ls->name);
// 		if (ls->next->name != NULL)
// 			ft_putstr("        ");
// 		ls = ls->next;
// 	}
// 	closedir(dir);
// }

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

void	ft_ls_dir(t_type *type, char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	t_ls			*ptr;
	t_ls			*ls;

	ls = malloc(sizeof(t_ls));
	dir = opendir((type->flag == 0) ? av : ".");
	if (!dir)
		print_error(av);
	while ((entry = readdir(dir)) != NULL)
	{
		ptr = malloc(sizeof(t_ls));
		ptr->name = entry->d_name;
		// ptr->flag = ls->flag;
		ptr->next = ls;
		ls = ptr;
		if (type->flag != 0)
			ft_ls_type(type, ls);
		else
			if (ls->name[0] == '.')
				ls = ls->next;
	}
	ls = sort_list(ls);
	// print(ls);
	while (ls->next != NULL)
	{
		ft_putstr(ls->name);
		if (ls->next->name != NULL)
			ft_putstr("        ");
		ls = ls->next;
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
	// ft_ls_dir(ls, dir, av);
}
//stat разобрать, там найдем нужные расширения
int     main(int ac, char **av)
{
	t_ls	*ls;
	t_type	*type;
	int		i;

	i = 2;

	if (!(type = malloc(sizeof(t_type))))
		exit(0);
	if (!(ls = malloc(sizeof(t_ls))))
		exit(0);

	ac = 0;

	ft_ls(type, av[1]);
	if (ac <= 2)
		ft_ls_dir(type, ".");
	else if (ac > 2)
	{
		i = 2;
		if (ft_ls(type, av[1]))
			printf("%d\n", type->flag);
		while (av[i])
		{
			ft_ls_dir(type, av[i]);
			i++;
		}
	}
}
