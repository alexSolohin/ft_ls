/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:55:26 by alex              #+#    #+#             */
/*   Updated: 2020/03/24 14:51:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>

void	print_error(char *av)
{
	ft_putstr("ls: ");
	ft_putstr(av);
	ft_putstr(": No such file or directory\n");
	exit(0);
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

void	get_flag(t_ls *ls, char *av)
{
	av = 0;
	if (ls->flag == 3)
		ft_ls_a(ls);
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

void	ft_ls_dir(t_ls *ls, char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	t_ls			*ptr;

	dir = opendir((ls->flag == 0) ? av : ".");
	if (!dir)
		print_error(av);
	while ((entry = readdir(dir)) != NULL)
	{
		ptr = malloc(sizeof(t_ls));
		ptr->name = entry->d_name;
		ptr->flag = ls->flag;
		ptr->next = ls;
		ls = ptr;
		if (ls->flag != 0)
		{
			get_flag(ls, av);
		}
		else
			if (ls->name[0] == '.')
				ls = ls->next;
	}
	ls = sort_list(ls);
	print(ls);
	// while (ls->next != NULL)
	// {
	// 	ft_putstr(ls->name);
	// 	if (ls->next->name != NULL)
	// 		ft_putstr("        ");
	// 	ls = ls->next;
	// }
	closedir(dir);
}

int		ft_ls(t_ls *ls, char *av)
{
	ls->flag = 0;
	if (ft_strequ(av, "-l"))
		ls->flag = 1;
	else if (ft_strequ(av, "-R"))
		ls->flag = 2;
	else if (ft_strequ(av, "-a"))
		ls->flag = 3;
	else if (ft_strequ(av, "-r"))
		ls->flag = 4;
	else if (ft_strequ(av, "-t"))
		ls->flag = 5;
	else
		return (0);
	return (1);
	// ft_ls_dir(ls, dir, av);
}
//stat разобрать, там найдем нужные расширения
int     main(int ac, char **av)
{
	t_ls	*ls;
	int		i;

	i = 2;
	ls = malloc(sizeof(t_ls));
	if (ac == 1)
		ft_ls_dir(ls, ".");
	else if (ac > 1)
	{
		if (ft_ls(ls, av[1]))
			printf("%d\n", ls->flag);
		while (av[i])
		{
			ft_ls(ls, av[i++]);
		}
	}

}
