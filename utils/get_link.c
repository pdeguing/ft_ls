/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 13:32:51 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/21 13:41:07 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

char	*get_link(t_file *file)
{
	char	*link;

	if (!S_ISLNK(file->stat->st_mode))
		return (NULL);
	link = (char *)malloc(sizeof(char) * (file->stat->st_size + 1));
	link[file->stat->st_size] = '\0';
	if (readlink(file->path, link, file->stat->st_size + 1) == -1)
	{
		file->error = 1;
		ft_printf("ls: %s: %s\n", file->name, strerror(errno));
		ft_strdel(&link);
		return (NULL);
	}
	return (link);
}
