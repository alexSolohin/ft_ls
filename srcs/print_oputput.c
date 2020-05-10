#include "ft_ls.h"

char		*get_user_name(uid_t user_id)
{
	t_user *usr;

	if (!(usr = getpwuid(user_id)))
	{
		ft_printf("Can't get struct for user: %d", user_id);
		exit(EXIT_FAILURE);
	}
	return (usr->pw_name);
}

char 		*get_group_name(gid_t group_id)
{
	t_group	*grp;

	if (!(grp = getgrgid(group_id)))
	{
		ft_printf("Can't get struct for group: %d", group_id);
		exit(EXIT_FAILURE);
	}
	return (grp->gr_name);
}

char		*get_time(t_time t)
{
	char	*fmt;
	if (time(NULL) > t.tv_sec + 15552000) /* 180 * 24 * 60 * 60 */
		fmt = ctime(t.tv_sec);

}
void		print_output(t_ls *ls)
{
	char	*uname;
	char	*gname;
	char	*time;

	if (!ls->flag.l || !ls->flag.g)
	{
		printname();
		return ;
	}
	gname = get_group_name(ls->gid);
	uname = get_user_name(ls->uid);
	time = get_time(ls->time);
}

//printf("name = %s\n", ls->path);
//int major = (int)(((file_stat.st_rdev) >> 16) & 0xffff);
//("major = %4u ", major);
//printf(", minor = %4u\n", (int)((file_stat.st_rdev) & 0xffff));