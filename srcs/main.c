/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 23:28:30 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/02 23:28:30 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_ls_node(t_ls *entry, t_ls **ls)
{
	t_ls	*tmp;

	if (!(tmp = (t_ls *)malloc(sizeof(t_ls))))
	{
		printf("%s", strerror(errno));	         //добавить обработку исключений
		return;
	}

	if(entry && ls)
	{
		*tmp = *entry;
		tmp->next = *ls;
		*ls = tmp;
	}
}
void 			free_list(t_ls *ls)
{
	t_ls		*cur;
	t_ls		*next;

	cur = ls;
	while (cur)
	{
		next = cur->next;
		free(cur->name);
		free(cur->path);
		free(cur->tm);
		free(cur->uname);
		free(cur->gname);
		free(cur->link);
		free(cur->chmod);
		free(cur);
		cur = next;
	}
}

int 			input_processing(t_flag flag, int ac, char **av)
{
	t_ls 		*fls;
	t_ls 		*dls;
	t_ls		entry;
	int			i;

	fls = NULL;
	dls = NULL;
	i = 0;
	while (i < ac)
	{
		if (!init_struct(&entry, flag, ft_strdup(av[i++]), 1))
			continue;
		if (!entry.flag.d && S_ISDIR(entry.mode))
			add_ls_node(&entry, &dls);
		else
			add_ls_node(&entry, &fls);
	}
	merge_sort(&fls);
	merge_sort(&dls);
	ft_ls(fls, 0, 0);
	free_list(fls);
	(fls && dls) ? ft_putchar('\n') : 0;
	ft_ls(dls, !flag.d, (dls && (fls || dls->next)) || flag.r_cap);
	free_list(dls);
	return (0);
}

int				main(int ac, char **av)
{
	t_flag		flag;
	char 		*cd;

	cd = CURR_DIR;
	collect_flags(&flag, &ac, &av);
	if (ac)
		input_processing(flag, ac, av);
	else
		input_processing(flag, 1, &cd);
	return (0);
}
