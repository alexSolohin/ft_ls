#include "ft_ls.h"

/**
 * -a --all
 * --color=auto --color=no
 * -d --directory
 * -f
 * -g
 * -r --reverse
 * -R --recursive
 * -l
 * -t
 * -u
 */

int				no_more_options(char **optcursor)
{
	*optcursor = NULL;
	return (-1);
}

t_opt 			*set_start_opt_val(void)
{
	t_opt		*opt;

	if(!(opt = (t_opt *)malloc(sizeof(t_opt))))
	{
		return (NULL);
		exit(-1);
	}
	opt->optind = 1;
	opt->optarg = NULL;
	opt->optchar = -1;
	opt->optdecl = NULL;
	return (opt);
}

void 			opt_has_arg(int ac, char **av, t_opt **opt, char **optcursor)
{
	if ((*opt)->optdecl)
	{
		if ((*opt)->optdecl[1] == ':')
		{
			(*opt)->optarg = (*optcursor)++;
			if (*((*opt)->optarg) == '\0')
			{
				if ((*opt)->optdecl[2] != ':')
				{
					if (++((*opt)->optind) < ac)
						(*opt)->optarg = av[(*opt)->optind];
					else
					{
						(*opt)->optarg = NULL;
						(*opt)->optchar = (FLAGS[0] == ':') ? ':' : '?';
					}
				}
				else
					(*opt)->optarg = NULL;
			}
			*optcursor = NULL;
		}
	}
	else
		(*opt)->optchar = '?';
}

int 			ft_getopt(int ac, char **av, t_opt *opt)
{
	static char	*optcursor = NULL;

	if (opt->optind >= ac || av[opt->optind] == NULL ||
		*av[opt->optind] != '-' || ft_strcmp(av[opt->optind], "-") == 0)
		return (no_more_options(&optcursor));
	if (ft_strcmp(av[opt->optind], "--") == 0)
	{
		(opt->optind)++;
		return (no_more_options(&optcursor));
	}
	if (optcursor == NULL || *optcursor == '\0')
		optcursor = av[opt->optind] + 1;
	opt->optchar = *optcursor;
	opt->optdecl = ft_strchr(FLAGS, opt->optchar);
	opt_has_arg(ac, av, &opt, &optcursor);
	if (optcursor == NULL || *(++optcursor) == '\0')
		(opt->optind)++;
	return (opt->optchar);
}

void 			collect_opt(int ac, char **av)
{
//	int 		*opt_collector;
	t_opt		*opt;
	int 		input_opt;

	opt = set_start_opt_val();
	while ((input_opt = ft_getopt(ac, av, opt)) != -1)
	{
		if (input_opt == 'd')
			ft_printf("ru ro raggy! %c\n", opt->optchar);
		if (input_opt == 'l')
			ft_printf("hell yeah, motherfucker! %c\n", opt->optchar);
		if (input_opt == '?')
			print_error("Move bitch! Get out da way!")
	}
}

int main(int ac, char **av)
{
	collect_opt(ac, av);
}