/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:04:58 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/05 14:10:01 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = malloc(size)))
		ft_errno(ENOMEM, NULL);
	ft_bzero(mem, size);
	return (mem);
}
