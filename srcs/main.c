#include "ft_ls.h"
#include <stdio.h>


int			main(int ac, char **av)
{
	t_flag	flag;
	int		args[get_num_of_array_index((t_input){ac, av})];

	reset_flags(&flag);
	collect_flags(args, &flag, (t_input){ac, av});
	return (0);
}