/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:55:26 by alex              #+#    #+#             */
/*   Updated: 2020/03/17 12:10:11 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    parser(char *str, t_ls *ls)
{
    if (ft_strequ(str, "-l"))
        ls->flag = 1;
    else if (ft_strequ(str, "-R"))
        ls->flag = 2;
    else if (ft_strequ(str, "-a"))
        ls->flag = 3;
    else if (ft_strequ(str, "-r"))
        ls->flag = 4;
    else if (ft_strequ(str, "-t"))
        ls->flag = 5;
    else
        ft_putendl("sory");


}

int     main(int ac, char **av)
{
    t_ls    *ls;

    ls = malloc(sizeof(t_ls));
    if (ac == 1)
        
    else if (ac == 2)
    {
        parser(av[1], ls);
    }
}
