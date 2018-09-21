/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 16:46:36 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/20 19:26:10 by pdeguing         ###   ########.fr       */
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

char	*get_user(t_flags *flags, uid_t st_uid)
{
	struct passwd	*user;

	user = getpwuid(st_uid);
	if (user == NULL || flags->n)
		return (ft_itoa(st_uid, 10));
	else
		return (ft_strdup(user->pw_name));
}

char	*get_grp(t_flags *flags, gid_t st_gid)
{
	struct group	*grp;

	grp = getgrgid(st_gid);
	if (grp == NULL || flags->n)
		return (ft_itoa(st_gid, 10));
	else
		return (ft_strdup(grp->gr_name));
}

void	get_stat(t_flags *flags, t_file *file)
{
	int		ret;

	file->stat = (t_stat *)malloc(sizeof(t_stat));
	if (flags->l && !flags->L)
		ret = lstat(file->path, file->stat);
	else
		ret = stat(file->path, file->stat);
	if (ret != 0)
	{
		file->error = 1;
		ft_printf("ls: %s: %s\n", file->name, strerror(errno));
	}
}

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

/*
** We create a new node and fill it with informations about the file.
** We had to add a string for the path in the file struct because stat
** does not work in sudbidrectories otherwise. Implementing error management
** is a priority, it would have allow us to identify this problem quickly.
*/

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
		flags->max_size = new->stat->st_size; // SAME HERE
	new->user = get_user(flags, new->stat->st_uid);
	if (ft_strlen(new->user) > flags->user_width)
		flags->user_width = ft_strlen(new->user); // COULD REPLACE BOTH LINES WITH A FUNCTION THAT RETURN BIGGEST INT
	new->grp = get_grp(flags, new->stat->st_gid);
	if (ft_strlen(new->grp) > flags->grp_width)
		flags->grp_width = ft_strlen(new->grp); // COULD REPLACE BOTH LINES WITH A FUNCTION THAT RETURN BIGGEST INT
	new->next = NULL;
	return (new);
}
