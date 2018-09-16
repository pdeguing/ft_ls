/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:05:07 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/15 19:45:29 by pdeguing         ###   ########.fr       */
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

t_file	*get_list(t_file *file, char *name)
{
	t_dirent	*entry;
	DIR			*dirp;
	t_file		*head;

	head = file;
	dirp = opendir(name);
	while ((entry = readdir(dirp)))
	{
			file->next = file_new(entry->d_name);
			file = file->next;
	}
	closedir(dirp);
	return (head);
}

void	start_list(t_flags *flags, char *name)
{
	t_file	*file;

	file = file_new(name); // THIS FUNCTION SHOULD GET THE INFOS
	if (S_ISDIR(file->stat.st_mode))
	{
		// DEL FILE
		file = get_list(file, name);
	}
	sort_list(flags, &file);
	print_list(flags, &file); // THIS FUNCTION SHOULD PRINT AND DELETE ALL NODES BUT DIR 
	if (flags->R)
	{
		// DO RECURSION
	}
	// FREE ENTIRE LIST
	return ;
}

	/*
	struct dirent	*entry;
	DIR				*dirp;

	ft_printf("%s:\n", name);
	dirp = opendir(name);
	while ((entry = readdir(dirp)))
		ft_printf("%s\n", entry->d_name); // PUT IN A LINKED LIST INSTEAD
	closedir(dirp);
	*/
