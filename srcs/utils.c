#include "ft_ls.h"

char		*get_user_name(uid_t user_id)
{
    t_user	*usr;
    char	*uname;

    if (!(usr = getpwuid(user_id)))
    {
        printf("Can't get struct for user: %d", user_id); // Добавить обработку ошибок
        exit(EXIT_FAILURE);
    }
    if (!(uname = ft_strdup(usr->pw_name)))
        exit(EXIT_FAILURE);
    return (uname);
}

char 		*get_group_name(gid_t group_id)
{
    t_group	*grp;
    char 	*gname;

    if (!(grp = getgrgid(group_id)))
    {
        printf("Can't get struct for group: %d", group_id); // Добавить обработку ошибок
        exit(EXIT_FAILURE);
    }
    if (!(gname = ft_strdup(grp->gr_name)))
        exit(EXIT_FAILURE);
    return (gname);
}

char		*get_tm(t_time t)
{
	char 	*tm;
	char 	*year;
	char 	*date;
	char 	*fmt;

	tm = ctime(&t.tv_sec);
	if ((time(NULL) > t.tv_sec + 15552000))
	{
		date = ft_strsub(tm, 4, 7);
		year = ft_strsub(tm, 19, 5);
		fmt = ft_strjoin(date, year);
		free(date);
		free(year);
	}
	else
		fmt = ft_strsub(tm, 4, 12);
	return  (fmt);
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

char        **create_arr(t_ls *ls, int  max_len_list)
{
    char **ptr;

    if (!(ptr = (char **)malloc(sizeof(char*) * max_len_list + 1)))
        return NULL;
    int i = 0;
    while (ls)
    {
        ptr[i] = ls->name ? ls->name : ls->path;
        ls = ls->next;
        i++;
    }
    ptr[i] = NULL;
    return (ptr);
}
