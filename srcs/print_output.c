#include "ft_ls.h"


char 		*lpath(char *linkname, mode_t mode)
{
	int		len;
	char	buf[MAX_PATH];
	char 	*res;
	char	*link;

	if (S_ISLNK(mode))
	{
		errno = 0;
		if ((len = readlink(linkname, buf, MAX_PATH)) < 0)
		{
			printf("ft_ls: cannot read symbolic link \'%s\': %s\n", linkname,
					strerror(errno));
			return (NULL);
		}
		buf[len] = '\0';
		res = ft_strdup(buf);
		link = ft_strjoin(" -> ", res);
		free(res);
		return (link);
	}
	return (NULL);
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
	if (S_ISDIR(ls->mode))
		printf("total %ld\n", total_blk(ls));
	while (ls)
	{
		printf("%*s %*u %-*s %-*s ", t.max_mode, ls->chmod, t.max_nlink,
				ls->nlink, t.max_name, ls->uname, t.max_name, ls->gname);
		if (S_ISBLK(ls->mode) || S_ISCHR(ls->mode))
			printf("%4d, %4d %s %s", mjr(ls), mnr(ls), ls->tm, ls->name);
		else
			printf("%*lu %s %s%s%s", t.max_size, ls->size, ls->tm,
				   "\x1b[31m", ls->name ? ls->name : ls->path, "\x1b[0m");
		if (ls->link)
			printf("%s", ls->link);
		printf("\n");
		ls = ls->next;
	}
}
