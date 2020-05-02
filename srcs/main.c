#include "ft_ls.h"
#include <stdio.h>


int			main(int ac, char **av)
{
	t_ls	*ls;
	char	**buff;
	ls = (t_ls*1zeof(t_ls));

	reset_flags(&(ls->flag));
	if (ac >= 2)
	{
		collect_flags(&(ls->flag), ac, &av);
		ft_printf("%s", *av);
		buff = ft_ls_dir(*av);
	}
	else
		//ft_ls_dir(".");
		ft_printf("---");
	return (0);
}
