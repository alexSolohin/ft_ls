/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:04:45 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/03 22:58:42 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *str)
{
	size_t	i;
	char	*tmp;

	i = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (NULL);
	ft_strcpy(tmp, str);
	return (tmp);
}
