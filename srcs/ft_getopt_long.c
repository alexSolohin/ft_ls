#include "ft_ls.h"

int 			find_val(t_input *input, t_lopt *o, t_opt **opt)
{
	int			retval;

	if (o->flag)
		*(o->flag) = o->val;
	retval = o->flag ? 0 : o->val;
	if (o->hasarg != NO_ARG)
	{
		(*opt)->optarg = ft_strchr(input->av[(*opt)->optind], '=');
		if ((*opt)->optarg != NULL)
			((*opt)->optarg)++;
		if (o->hasarg == REQ_ARG)
		{
			if ((*opt)->optarg == NULL && ++((*opt)->optind) < input->ac)
				(*opt)->optarg = input->av[(*opt)->optind];
			if ((*opt)->optarg == NULL)
				retval = ':';
		}
	}
	else if (ft_strchr(input->av[(*opt)->optind], '='))
		retval = '?';
	return (retval);
}

int			find_matches(t_lopt *o, t_lopt **match, const char *cur, size_t len)
{
	int 	num_matches;

	num_matches = 0;
	while (o->name)
	{
		if (strncmp(o->name, cur, len) == 0)
		{
			*match = o;
			num_matches++;
		}
		o++;
	}
	return (num_matches);
}

int				get_lopt(t_input input, t_opt *opt, t_lopt *lopt, int *longind)
{
	t_lopt 		*o;
	t_lopt 		*match;
	size_t		arg_name_length;
	const char	*curr_arg;
	int 		retval;

	o = lopt;
	match = NULL;
	if (opt->optind >= input.ac)
		return (-1);
	if (ft_strlen(input.av[opt->optind]) < 3 ||
		ft_strncmp(input.av[opt->optind], "--", 2) != 0)
		return (ft_getopt(input, opt, FLAGS));
	curr_arg = input.av[opt->optind] + 2;
	arg_name_length = strcspn(curr_arg, "="); //реализовать ф-ию strcspn
	if (find_matches(o, &match, curr_arg, arg_name_length) == 1)
	{
		if (longind)
			*longind = (int)(match - lopt);
		retval = find_val(&input, match, &opt);
	}
	else
		retval = '?';
	++(opt->optind);
	return (retval);
}

int 		ft_getopt_long(t_input data, t_opt *opt, t_lopt *lopt, int *longind)
{
	int ret;

	return (ret = get_lopt(data, opt, lopt, longind));
}

/*int			main(int ac, char **av)
{
	t_opt	*opt;
	t_lopt	*lopt;
	const char* short_options = "hs::f:";
	int rez;
	int option_index = -1;
	opt = NULL;
	opt = set_start_opt_val(opt);
	t_lopt long_options[] = {
			{"help",NO_ARG,NULL,'h'},
			{"size",OPT_ARG,NULL,'s'},
			{"file",REQ_ARG,NULL,'f'},
			{NULL,0,NULL,0}
	};

	while ((rez=ft_getopt_long((t_input){ac, av}, opt, long_options, &option_index))!= -1)
	{
		switch(rez){
			case 'h': {
				ft_printf("This is demo help. Try -h or --help.\n");
				if (option_index<0)
					ft_printf("short help option\n");
				else
				{

					ft_printf("option_index = %d (\"%s\",%d,%c)\n",
						   option_index,
						   long_options[option_index].name,
						   long_options[option_index].hasarg,
						   long_options[option_index].val);
				}
				break;
			};
			case 's': {
				if (opt->optarg!=NULL)
					ft_printf("found size with value %s\n", opt->optarg);
				else
					ft_printf("found size without value\n");
				break;
			};

			case 'f': {
				ft_printf("file = %s\n", opt->optarg);
				ft_printf("option_index = %d (\"%s\",%d,%c)\n",
					   option_index,
					   long_options[option_index].name,
					   long_options[option_index].hasarg,
					   long_options[option_index].val);
				break;
			};
			case '?': default: {
				ft_printf("found unknown option\n");
				break;
			};
		};
		option_index = -1;
	};
	return 0;
}*/
