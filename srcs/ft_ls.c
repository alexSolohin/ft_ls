/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:55:26 by alex              #+#    #+#             */
/*   Updated: 2020/04/23 17:21:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

//	parser to file
//	opendir(../dir)
//		while (entry = readdir())

int		sort_alphabet(char *a, char *b)
{
	int i;

	i = 0;
	while (b[i])
	{
		if (a[i] > b[i])
			return (1);
		else
			return (0);
		i++;
	}
	return (1);
}

t_ls	*sort_list(t_ls *ls)
{
//	char	*tmp;
	int		type_a;
	t_ls	*ptr;
	t_ls	*tmp;

// struct list * sort( struct list *root )
// {
//     struct list *new_root = NULL;

//     while ( root != NULL )
//     {
//         struct list *node = root;
//         root = root->next;

//         if ( new_root == NULL || node->data < new_root->data )
//         {
//             node->next = new_root;
//             new_root = node;
//         }
//         else
//         {
//             struct list *current = new_root;
//             while ( current->next != NULL && !( node->data < current->next->data ) )
//             {
//                   current = current->next;
//             }

//             node->next = current->next;
//             current->next = node;
//         }
//     }

//     return new_root;
// }

	ptr = NULL;
	type_a = 0;
	while (ls != NULL)
	{
		// if (ls->name[0] == '.' && type_a != 1)
		tmp = ls;
		ls = ls->next;
		if (ptr == NULL || sort_alphabet(tmp->name, ptr->name))
		{
			tmp->next = ptr;
			ptr = tmp;
		}
		else
		{
			t_ls *current = ptr;
			while (current->next != NULL && !sort_alphabet(tmp->name, current->next->name))
			{
				current = current->next;
			}
			tmp->next = current->next;
			current->next = tmp;
		}
	}
	return (ptr);
}

void	ft_ls_dir(char *av)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;
	t_ls			*ls;
	t_ls			*ptr;

	if (!(ls = malloc(sizeof(t_ls))))
		exit(0);
	dir = opendir(av);
	if (!dir)
		exit(0);
	if (!(path = malloc(sizeof(char) * 255)))
		exit(0);
	path = ft_strcpy(path, av);
	path[ft_strlen(av)] = '/';
	while ((entry = readdir(dir)) != NULL)
	{
		ptr = malloc(sizeof(t_ls));
		ptr->name = entry->d_name;
		ptr->path = ft_strdup(path);
		ptr->path = ft_strcat(ptr->path, entry->d_name);
		init_struct(ptr, av);
		ptr->next = ls;
		ls = ptr;
		free(ptr->path);
	}
	// sort_list(ls);
	while (ls->next != NULL)
	{
		int i = 0;
		while (i < 10)
			printf("%c", ls->chmod[i++]);
		printf(" %d %s %s", ls->links, ls->group_name, ls->user_name);
		printf(" %d %.16s %s\n", ls->byte_size, ls->time, ls->name);
		ls = ls->next;
	}
	closedir(dir);
}

int     main(int ac, char **av)
{
	ac = 0;
	ft_ls_dir(av[1]);
}
