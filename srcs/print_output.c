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
		ft_printf("%*s %*u %-*s %-*s ", t.max_mode, ls->chmod, t.max_nlink,
				ls->nlink, t.max_name, ls->uname, t.max_name, ls->gname);
		if (S_ISBLK(ls->mode) || S_ISCHR(ls->mode))
			ft_printf("%4d, %4d %s ", mjr(ls), mnr(ls), ls->tm);
		else
			ft_printf("%*lu %s ", t.max_size, ls->size, ls->tm);
//		set_color(ls->mode, ls->flag.g);
//		ft_printf("{BLUE}");
		ft_printf("{BLUE}%s{EOC}", ls->name ? ls->name : ls->path);
		if (ls->link)
			printf("%s", ls->link);
		printf("\n");
		ls = ls->next;
	}
}
