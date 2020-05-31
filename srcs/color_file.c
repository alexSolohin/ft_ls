#include "ft_ls.h"

char 	*color_file(mode_t mode, int do_color)
{
	if (!do_color)
		return (NULL);

	return (mode ? "color" : NULL);
}

