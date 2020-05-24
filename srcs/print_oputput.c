#include "ft_ls.h"
#include <errno.h>
#include <time.h>

char 		*lpath(char *linkname)
{
	int		len;
	char	link[MAX_PATH];
	char 	ret[MAX_PATH];

	errno = 0;
	if ((len = readlink(linkname, link, MAX_PATH)) < 0)
	{
		printf("%s", strerror(errno)); 		// Добавить обработку ошибок
		return ("?");
	}
	link[len] = '\0';
	return (ft_strcpy(ret, link));
}

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
		print_column(ls);
		return;
	}
	t = print_utils(ls);
	printf("total %ld\n", total_blk(ls));
	while (ls)
	{
		printf("%*s %*u %-*s %-*s ", t.max_mode, ft_chmod(ls), t.max_nlink,
				ls->nlink, t.max_name, ls->uname, t.max_name, ls->gname);
		if (S_ISBLK(ls->mode) || S_ISCHR(ls->mode))
		{
			printf("%4d, %4d %s %s", mjr(ls), mnr(ls), ls->tm, ls->name);
		}
		else
			printf("%*lu %s %s", t.max_size, ls->size, ls->tm, ls->name);
		S_ISLNK(ls->mode) ? printf(" -> %s\n", lpath(ls->path)) : printf(
				"\n");
		ls = ls->next;
	}
	ft_putchar('\n');
}
