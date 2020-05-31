#include "ft_ls.h"

void	set_color(mode_t mode, int do_color)
{
	if (!do_color)
		return ;
	if (S_ISDIR(mode))
		ft_printf("{BLUE}");
}

