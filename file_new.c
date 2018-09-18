/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 16:46:36 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/17 14:21:00 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Getting the name from the path by duplicating after the last slash
*/

char	*get_name(char *path)
{
	char	*name;
	int		i;

	i = ft_strlen(path) - 1;
	while (i > 0 && path[i] == '/')
		i--;
	while (i >= 0 && path[i] != '/')
		i--;
	name = ft_strdup(path + i + 1);
	return (name);
}

/*
** We create a new node and fill it with informations about the file.
** We had to add a string for the path in the file struct because stat
** does not work in sudbidrectories otherwise. Implementing error management
** is a priority, it would have allow us to identify this problem quickly.
*/

t_file	*file_new(char *path)
{
	t_file	*new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->path = path;
	new->name = get_name(path);
	if (stat(path, &new->stat) == -1)
	{
		perror("stat: ");
	}
	new->user = getpwuid(new->stat.st_uid);
	if (new->user == NULL)
		perror("getpwuid: ");
	new->group = getgrgid(new->stat.st_gid);
	if (new->group == NULL)
		perror("getgrgid: ");
	new->next = NULL;
	return (new);
}
