/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 10:13:05 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/15 18:29:15 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

int		main(int argc, char **argv)
{
	DIR				*dirp;
	struct dirent	*entry;

	if (argc != 2)
		return (0);
	dirp = opendir(argv[1]);
	while ((entry = readdir(dirp)) != NULL)
		printf("%s\n", entry->d_name);
	closedir(dirp);
}
