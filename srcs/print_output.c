/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 02:35:51 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/03 16:53:35 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void 		print_column(t_ls *ls)
{

	if (ls)
	{
		while(ls)
		{
			ft_putstr(ls->name ? ls->name : ls->path);
			write(1, "\n", 1);
			ls = ls->next;
		}
	}
}

void		print_long_info(t_ls *ls, t_print t)
{
	if (!ls->flag.g)
		ft_printf("%*s %*u %-*s %-*s ", t.max_mode, ls->chmod, t.max_nlink,
					ls->nlink, t.max_uname, ls->uname, t.max_gname,  ls->gname);
	else
		ft_printf("%*s %*u %-*s ", t.max_mode, ls->chmod, t.max_nlink,
				  ls->nlink, t.max_gname,  ls->gname);
	if (S_ISBLK(ls->mode) || S_ISCHR(ls->mode))
		ft_printf("%*u, %*u %s ", t.max_mjr, mjr(ls),
				t.max_mnr, mnr(ls), ls->tm);
	else
		ft_printf("%*lu %s ", t.max_size, ls->size, ls->tm);
}

void		print_output(t_ls *ls)
{
	t_print	t;

	if (!ls->flag.l && !ls->flag.g)
	{
		print_column(ls);
		return;
	}
	t = print_utils(ls);
	while (ls)
	{
		print_long_info(ls, t);
		set_color(ls->mode, ls->flag.G);
		ft_printf("%s", ls->name ? ls->name : ls->path);
		ft_putstr(RESET);
		S_ISLNK(ls->mode) ? ft_printf("%s\n", ls->link) : ft_putchar('\n');
		ls = ls->next;
	}
}
