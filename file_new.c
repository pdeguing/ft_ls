/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 16:46:36 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/22 10:26:19 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*file_new(t_flags *flags, char *path, int is_arg)
{
	t_file	*new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->path = path;
	new->name = get_name(path);
	new->is_arg = is_arg;
	new->error = 0;
	get_stat(flags, new);
	new->link = get_link(new);
	if (new->stat->st_size > flags->max_size)
		flags->max_size = new->stat->st_size;
	new->user = get_user(flags, new->stat->st_uid);
	if (ft_strlen(new->user) > flags->user_width)
		flags->user_width = ft_strlen(new->user);
	new->grp = get_grp(flags, new->stat->st_gid);
	if (ft_strlen(new->grp) > flags->grp_width)
		flags->grp_width = ft_strlen(new->grp);
	new->next = NULL;
	return (new);
}
