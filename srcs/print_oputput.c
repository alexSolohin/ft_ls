#include "ft_ls.h"
#include <errno.h>
#include <time.h>

static void 	print_name()
{

}

static char		*get_user_name(uid_t user_id)
{
	t_user *usr;

	if (!(usr = getpwuid(user_id)))
	{
		printf("Can't get struct for user: %d", user_id); // Добавить обработку ошибок
		exit(EXIT_FAILURE);
	}
	return (usr->pw_name);
}

static char 		*get_group_name(gid_t group_id)
{
	t_group	*grp;

	if (!(grp = getgrgid(group_id)))
	{
		printf("Can't get struct for group: %d", group_id); // Добавить обработку ошибок
		exit(EXIT_FAILURE);
	}
	return (grp->gr_name);
}

static char		*get_time(t_time t)
{
	char	*fmt;
	char 	*tm;

	//ft_bzero(fmt, 32);
	tm = ctime(&t.tv_sec);
    return  ((time(NULL) > t.tv_sec + 15552000) ?
		ft_strcat(ft_strsub(tm, 4, 7), ft_strsub(tm, 20, 4)) :
		ft_strsub(tm, 4, 12));
//	return (fmt);
}

char 		*lpath(char *linkname)
{
	int		len;
	char	link[MAX_PATH];

	errno = 0;
	if ((len = readlink(linkname, link, MAX_PATH)) < 0)
	{
		printf("%s", strerror(errno)); 		// Добавить обработку ошибок
		return ("?");
	}
	link[len] = '\0';
	return (ft_strdup(link));
}

void		print_output(t_ls *ls)
{
//	char 	*mode;
	char	*uname;
	char	*gname;
//	char	*time;

	if (!ls->flag.l && !ls->flag.g)
	{
		printf("%s", ls->name);
		return ;
	}
//	mode = ft_chmod(ls);
	gname = get_group_name(ls->gid);
	uname = get_user_name(ls->uid);
//	time = get_time(ls->time);
	printf("%s %u %-1.8s %-8.8s ", ft_chmod(ls), ls->nlink, uname, gname);
	if (S_ISBLK(ls->mode) || S_ISCHR(ls->mode))
	{
		printf("%4u, %4u %s %s", (int)(((ls->rdev) >> 16) & 0xffff),
			   (int)((ls->rdev) & 0xffff), get_time(ls->time), ls->name);
	}
	else
		printf("%10lu %s %s", (unsigned long)ls->byte_size, get_time(ls->time), ls->name);
	S_ISLNK(ls->mode) ? printf(" -> %s\n", lpath(ls->name)) : printf("\n");
}
