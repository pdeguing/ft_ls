/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 16:46:36 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/15 18:34:27 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** We create a new node and fill it with informations about the file
*/

t_file	*file_new(char *name)
{
	t_file	*new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->f_name = name;
	if (!stat(name, &new->stat))
	{
		// PRINT ERROR
	}
	new->user = getpwuid(new->stat.st_uid);
	new->group = getgrgid(new->stat.st_gid);
	new->next = NULL;
	return (new);
}
