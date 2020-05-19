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
	char	*uname;
	char	*gname;

	if (ls && !ls->flag.l && !ls->flag.g)
	{
		print_column(ls);
		return ;
	}
	printf("total %ld\n", total_blk(ls));
	while (ls)
	{
		uname = get_user_name(ls->uid);
		gname = get_group_name(ls->gid);
		printf("%s %u %-1.8s %-1.8s ", ft_chmod(ls), ls->nlink, uname, gname);
		if (S_ISBLK(ls->mode) || S_ISCHR(ls->mode))
		{
			printf("%4u, %4u %s %s", (int)(((ls->rdev) >> 16) & 0xffff),
				   (int)((ls->rdev) & 0xffff), get_time(ls->time), ls->name);
		}
		else
			printf("%7lu %s %s", ls->size, get_time(ls->time), ls->name);
		S_ISLNK(ls->mode) ? printf(" -> %s\n", lpath(ls->path)) : printf("\n");
		ls = ls->next;
	}
	ft_putchar('\n');
}
