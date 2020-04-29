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
		flag->a_flag = 1;
	else if (rez == 'd')
		flag->d_flag = 1;
	else if (rez == 'f')
		flag->f_flag = 1;
	else if (rez == 'g')
		flag->g_flag = 1;
	else if (rez == 'l')
		flag->l_flag = 1;
	else if (rez == 'R')
		flag->rec_flag = 1;
	else if (rez == 'r')
		flag->r_flag = 1;
	else if (rez =='t')
		flag->t_flag = 1;
	else
		flag->u_flag = 1;
}

void 		collect_flags(t_flag *flag, int ac, char ***av)
{
	t_opt	*opt;
	int 	rez;
	int 	opt_index;
	t_input	tmp;

	tmp.av = *av;
	tmp.ac = ac;
	opt = NULL;
		while ((rez = ft_getopt_long(tmp, &opt, g_lopt, &opt_index)) != -1)
		{
			if (rez == '?')
				invalid_option(opt);
			set_flag(rez, flag);
		}
		*av += opt->optind;
		free(opt);
}

int 		get_num_of_array_index(t_input input)
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
}

void		reset_flags(t_flag *flag)
{
	flag->a_flag = 0;
	flag->d_flag = 0;
	flag->f_flag = 0;
	flag->g_flag = 0;
	flag->l_flag = 0;
	flag->rec_flag = 0;
	flag->r_flag = 0;
	flag->t_flag = 0;
	flag->u_flag = 0;
}
