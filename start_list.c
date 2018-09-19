/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:05:07 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/19 11:48:17 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

	// 1. GET INFO ABOUT THE FILE (IF ERROR, EXIT)
	// 2. IF DIRECTORY: -> STORE ALL ENTRIES IN LINKED LIST
	// 					-> GET INFO ABOUT FILES
	// 					-> SORT LINKED LIST DEPENDING ON FLAG
	// 3. PRINT INFO DEPENDING ON FLAGS AND DELETE NODE IF NO -R (IF ERROR, PRINT ERROR)
	// 4. IF -R, DON'T DEL DIRECTORIES IN LIST, RECURSION WHILE NODE LEFT
	// 5. RETURN 

/*
** Delete the first file of the list and update the start of the list
*/

void	del_node(t_file **list)
{
	t_file	*head;

	head = *list;
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
	if (S_ISDIR((*list)->stat.st_mode) && flags->R && (*(*list)->name != '.' || flags->a))
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
	if (head->path[ft_strlen(head->path) - 1] != '/') // APPARENTLY CONDITION NOT NEEDED
		head->path = ft_strffjoin(head->path, "/");
	if (dirp == NULL)
	{
		perror("opendir: ");
	}
	while ((entry = readdir(dirp)))
	{
		head->next = file_new(flags, ft_strjoin((*list)->path, entry->d_name));
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
	*list = file_new(flags, ft_strdup(path));
	if (S_ISDIR((*list)->stat.st_mode))
	{
		get_list(flags, list);
		del_node(list);
	}
	merge_sort(flags, list);
	print_list(flags, list);
	del_list(flags, list);
}

// SYMLINK / + and @ / last permission char / date if > 6 months from present / long format for socket and fifo and devices
// ADD * TO FT_PRINTF AND REPLACE PRINTF WITH FT_PRINTF IN PRINT FUNCTIONS
// FORMAT ERRORS DISPLAY -> should dispay "ls: <filename>: <strerror>\n"
// LEAKS -> do we have to free stat and passwd/grp struct? remeber to free allocated strings in struct
