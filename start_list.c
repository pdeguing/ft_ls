/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:05:07 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/27 09:37:11 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	del_list(t_flags *flags, t_file **list)
{
	if (!*list)
		return ;
	if (RECURSE_DIR && SHOW_INV)
	{
		if (NOT_PARENT && NOT_DOT)
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

void	get_list(t_flags *flags, t_file **list)
{
	t_dirent	*entry;
	DIR			*dirp;
	t_file		*head;
	char		*child_path;

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
		child_path = ft_strjoin((*list)->path, entry->d_name);
		head->next = file_new(flags, child_path, 0);
		head = head->next;
	}
	closedir(dirp);
}

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
