#include "ft_ls.h"

void		add_ls_node(t_ls *entry, t_ls **ls)
{
	t_ls	*tmp;

	if (!(tmp = (t_ls *)malloc(sizeof(t_ls))))
	{
		strerror(errno);                //добавить обработку исключений
		return;
	}
	if(entry && ls)
	{
		*tmp = *entry;
		tmp->next = *ls;
		*ls = tmp;
	}
}

int 			input_processing(t_flag flag, int ac, char **av)
{
	t_ls 		*fls;
	t_ls 		*dls;
	t_ls 		entry;
	int			i;

	fls = NULL;
	dls = NULL;
	i = 0;
	while (i < ac)
	{
		if (!init_struct(&entry, flag, av[i++]))
			continue;
		if (!entry.flag.d && entry.d_mode)
			add_ls_node(&entry, &dls);
		else
			add_ls_node(&entry, &fls);
	}
	merge_sort(&fls);
	merge_sort(&dls);
//	ft_ls(fls, dls->next || (dls && fls));
//	free(fls);
//	ft_ls(dls, dls->next || (dls && fls));
//	free(dls);
}

int				main(int ac, char **av)
{
	t_flag		flag;

	collect_flags(&flag, &ac, &av);
	if (ac)
		input_processing(flag, ac, av);
	else
		ft_ls_dir(CURR_DIR);
	return (0);
}
