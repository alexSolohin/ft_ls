#include "ft_ls.h"
#include <errno.h>
#include <time.h>

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
		write(1, "\n", 1);
	}
}

void		print_output(t_ls *ls)
{
		t_print	t;

	if (!ls->flag.l && !ls->flag.g)
	{
		print(ls);
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
		set_color(ls->mode, ls->flag.G);
		ft_printf("%s", ls->name ? ls->name : ls->path);
		ft_putstr(RESET);
		if (ls->link)
			ft_printf("%s", ls->link);
		ft_printf("\n");
		ls = ls->next;
	}
}
