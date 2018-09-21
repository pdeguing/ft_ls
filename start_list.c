/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:05:07 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/20 19:31:27 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Delete the first file of the list and update the start of the list
*/

void	del_node(t_file **list)
{
	t_file	*head;

	head = *list;
	ft_strdel(&head->path);
	ft_strdel(&head->name);
	ft_strdel(&head->user);
	ft_strdel(&head->grp);
	ft_strdel(&head->link);
	free(head->stat);
	*list = head->next;
	free(head);
	head = NULL;
}

/*
** We free the entire list unless recursion is on and the file is a directory.
** In that case, we call start_list() again for each directory we encounter.
*/

void	del_list(t_flags *flags, t_file **list)
{
	if (!*list)
		return ;
	if (S_ISDIR((*list)->stat->st_mode) && flags->R && (*(*list)->name != '.' || flags->a))
	{
		if (*((*list)->name + 1) && *((*list)->name + 1) != '.' && *((*list)->name + 1) != '/')
		{
			ft_printf("\n%s:\n", (*list)->path);
			start_list(flags, (*list)->path);
		}
		del_node(list);
	}
	else
		del_node(list);
	if (*list)
		del_list(flags, list);
}

/*
** This function returns a list containing a file node for each entry in the directory
*/

void	get_list(t_flags *flags, t_file **list)
{
	t_dirent	*entry;
	DIR			*dirp;
	t_file		*head;

	head = *list;
	dirp = opendir(head->path);
	if (head->path[ft_strlen(head->path) - 1] != '/')
		head->path = ft_strffjoin(head->path, "/");
	if (dirp == NULL)
	{
		head->error = 1;
		ft_printf("ls: %s: %s\n", head->name, strerror(errno));
		return ;
	}
	while ((entry = readdir(dirp)))
	{
		head->next = file_new(flags, ft_strjoin((*list)->path, entry->d_name), 0);
		head = head->next;
	}
	closedir(dirp);
}

/*
** Master function of the program, it is in charge of putting together all
** the other functions. This way we can work on small instruction blocks.
*/

void	start_list(t_flags *flags, char *path)
{
	t_file	**list;

	if (!(list = (t_file **)malloc(sizeof(t_file *))))
		return ;
	*list = file_new(flags, ft_strdup(path), 0);
	if (S_ISDIR((*list)->stat->st_mode))
	{
		get_list(flags, list);
		if (flags->l && !(*list)->error && S_ISDIR((*list)->stat->st_mode))
			ft_printf("total %llu\n", get_blkcnt(flags, list));
		del_node(list);
	}
	merge_sort(flags, list);
	print_list(flags, list);
	del_list(flags, list);
	free(list);
}
