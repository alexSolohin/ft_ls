#include "ft_ls.h"

char		*get_user_name(uid_t user_id)
{
	t_user *usr;

	if (!(usr = getpwuid(user_id)))
	{
		printf("Can't get struct for user: %d", user_id); // Добавить обработку ошибок
		exit(EXIT_FAILURE);
	}
	return (usr->pw_name);
}

char 		*get_group_name(gid_t group_id)
{
	t_group	*grp;

	if (!(grp = getgrgid(group_id)))
	{
		printf("Can't get struct for group: %d", group_id); // Добавить обработку ошибок
		exit(EXIT_FAILURE);
	}
	return (grp->gr_name);
}

char		*get_time(t_time t)
{
	char 	*tm;

	tm = ctime(&t.tv_sec);
	return  ((time(NULL) > t.tv_sec + 15552000) ?
			 ft_strcat(ft_strsub(tm, 4, 7), ft_strsub(tm, 20, 4)) :
			 ft_strsub(tm, 4, 12));
}

int64_t		total_blk(t_ls *ls)
{
	int64_t total;

	total = 0;
	if (ls)
	{
		while(ls)
		{
			total += ls->block;
			ls = ls->next;
		}
	}
	return (total);
}