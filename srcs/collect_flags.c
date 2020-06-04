/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 22:04:36 by user              #+#    #+#             */
/*   Updated: 2020/06/04 19:52:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		invalid_option(t_opt *opt)
{
	ft_printf("ft_ls: illegal option -- %s\n", opt->optopt);
	ft_printf("usage: ls [-GRadfglrtu1] [file ...]\n");
	free(opt);
	exit(0);
}

int 		is_colorize(char *opt_arg)
{
	int 	i;

	i = 0;
	if (opt_arg)
	{
		while (opt_arg[i])
		{
			opt_arg[i] = ft_tolower(opt_arg[i]);
			i++;
		}
		return (ft_strcmp(opt_arg, "on") == 0 ? COLOR_ON : COLOR_OFF);
	}
	else
		return (COLOR_ON);
}

void 		set_flag(int rez, t_flag *flag)
{
	if (rez == '1')
		flag->one = 1;
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
	flag->one = 0;
	flag->a = 0;
	flag->d = 0;
	flag->f = 0;
	flag->G = COLOR_OFF;
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
	t_input	tmp;

	reset_flags(flag);
	tmp.av = *av;
	tmp.ac = *ac;
	opt = NULL;
	while ((rez = ft_getopt_long(tmp, &opt, g_lopt, NULL)) != -1)
	{
		if (rez == '?')
			invalid_option(opt);
		if (rez == 'G')
		{
			flag->G = is_colorize(opt->optarg);
			continue ;
		}
		set_flag(rez, flag);
	}
	*av += opt->optind;
	*ac -= opt->optind;
	free(opt);
}
