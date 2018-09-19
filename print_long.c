/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 14:22:56 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/19 11:48:16 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_permissions(mode_t st_mode)
{
		printf("%c", (st_mode & S_IRUSR) ? 'r' : '-');
		printf("%c", (st_mode & S_IWUSR) ? 'w' : '-');
		printf("%c", (st_mode & S_IXUSR) ? 'x' : '-');
		printf("%c", (st_mode & S_IRGRP) ? 'r' : '-');
		printf("%c", (st_mode & S_IWGRP) ? 'w' : '-');
		printf("%c", (st_mode & S_IXGRP) ? 'x' : '-');
		printf("%c", (st_mode & S_IROTH) ? 'r' : '-');
		printf("%c", (st_mode & S_IWOTH) ? 'w' : '-');
		printf("%c ", (st_mode & S_IXOTH) ? 'x' : '-');
}

void	print_type(mode_t st_mode)
{
    if(S_ISREG(st_mode))
        printf("-");
    if(S_ISDIR(st_mode))
        printf("d");
    if(S_ISBLK(st_mode))
        printf("b");
    if(S_ISCHR(st_mode))
        printf("c");
    if(S_ISSOCK(st_mode))
        printf("s");
    if(S_ISLNK(st_mode))
        printf("l");
    if(S_ISFIFO(st_mode))
        printf("p");
}

void	print_long(t_flags *flags, t_file *file)
{
	print_type(file->stat.st_mode);
	print_permissions(file->stat.st_mode);
	printf(" %2d", file->stat.st_nlink);
	printf(" %-*s", flags->user_width, file->user);
	printf("  %-*s", flags->grp_width, file->grp);
	if (!flags->h)
		printf(" %*llu", ft_intlen(flags->max_size, 10), file->stat.st_size);
	printf(" %.12s", ctime(&file->stat.st_mtimespec.tv_sec) + 4);
	printf(" %s\n", file->name);
}
