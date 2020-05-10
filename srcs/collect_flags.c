#include "ft_ls.h"

void		invalid_option(t_opt *opt)
{
	ft_printf("ft_ls: invalid option -- \'%s\'", opt->optopt);
	free(opt);
	exit(0);
}

void 		set_flag(int rez, t_flag *flag)
{
	if (rez == 'a')
		flag->a = 1;
	else if (rez == 'd')
		flag->d = 1;
	else if (rez == 'f')
	{
		flag->a = 1;
		flag->f = 1;
	}
	else if (rez == 'g')
		flag->g = 1;
	else if (rez == 'l')
		flag->l = 1;
	else if (rez == 'R')
		flag->r_cap = 1;
	else if (rez == 'r')
		flag->r = 1;
	else if (rez =='t')
		flag->t = 1;
	else
		flag->u = 1;
}

void		reset_flags(t_flag *flag)
{
	flag->a = 0;
	flag->d = 0;
	flag->f = 0;
	flag->g = 0;
	flag->l = 0;
	flag->r_cap = 0;
	flag->r = 0;
	flag->t = 0;
	flag->u = 0;
}

void 		collect_flags(t_flag *flag, int *ac, char ***av)
{
	t_opt	*opt;
	int 	rez;
	int 	opt_index;
	t_input	tmp;

	reset_flags(flag);
	tmp.av = *av;
	tmp.ac = *ac;
	opt = NULL;
	while ((rez = ft_getopt_long(tmp, &opt, g_lopt, &opt_index)) != -1)
	{
		if (rez == '?')
			invalid_option(opt);
		set_flag(rez, flag);
	}
	*av += opt->optind;
	*ac -= opt->optind;
	free(opt);
}

/*int 		get_num_of_array_index(t_input input)
{
	int 	num;
	int 	i;
	int 	j;

	i = 1;
	num = 0;
	while (i < input.ac)
	{
		while (input.av[i]  != NULL)
		{
			j = 0;
			if (input.av[i] && input.av[i][j] == '-'
				&& input.av[i][j + 1] != '-' && input.av[i][j + 1] != '\0')
			{
				while (input.av[i][++j])
					num++;
				i++;
				break;
			}
			num++;
			i++;
		}
	}
	return (num);
}*/
