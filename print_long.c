/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 14:22:56 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/27 11:46:56 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_date(time_t *mtime)
{
	time_t	timedif;
	char	*strtime;

	timedif = time(NULL) - *mtime;
	strtime = ctime(mtime);
	if (!IS_RECENT(timedif))
		ft_printf(" %.6s %5.4s", strtime + 4, strtime + 20);
	else
		ft_printf(" %.12s", strtime + 4);
}

void	print_permissions(mode_t st_mode)
{
	ft_printf("%c", (st_mode & S_IRUSR) ? 'r' : '-');
	ft_printf("%c", (st_mode & S_IWUSR) ? 'w' : '-');
	ft_printf("%c", execution_mode(st_mode, S_IXUSR));
	ft_printf("%c", (st_mode & S_IRGRP) ? 'r' : '-');
	ft_printf("%c", (st_mode & S_IWGRP) ? 'w' : '-');
	ft_printf("%c", execution_mode(st_mode, S_IXGRP));
	ft_printf("%c", (st_mode & S_IROTH) ? 'r' : '-');
	ft_printf("%c", (st_mode & S_IWOTH) ? 'w' : '-');
	ft_printf("%c", execution_mode(st_mode, S_IXOTH));
}

void	print_type(mode_t st_mode)
{
	if (S_ISREG(st_mode))
		ft_printf("-");
	if (S_ISDIR(st_mode))
		ft_printf("d");
	if (S_ISBLK(st_mode))
		ft_printf("b");
	if (S_ISCHR(st_mode))
		ft_printf("c");
	if (S_ISSOCK(st_mode))
		ft_printf("s");
	if (S_ISLNK(st_mode))
		ft_printf("l");
	if (S_ISFIFO(st_mode))
		ft_printf("p");
}

void	print_size(t_flags *flags, t_stat *stat)
{
	if (S_ISBLK(stat->st_mode) || S_ISCHR(stat->st_mode))
		ft_printf(" %4d, %3d", MAJOR(stat->st_rdev), MINOR(stat->st_rdev));
	else
		ft_printf(" %*llu", ft_intlen(flags->max_size, 10), stat->st_size);
}

void	print_long(t_flags *flags, t_file *file)
{
	print_type(file->stat->st_mode);
	print_permissions(file->stat->st_mode);
	ft_printf("%c", file->xattr);
	ft_printf(" %2d", file->stat->st_nlink);
	ft_printf(" %-*s", flags->user_width, file->user);
	ft_printf("  %-*s ", flags->grp_width, file->grp);
	print_size(flags, file->stat);
	print_date(&file->stat->st_mtimespec.tv_sec);
	ft_printf(" %s", file->name);
	if (S_ISLNK(file->stat->st_mode) && !flags->L)
		ft_printf(" -> %s", file->link);
	ft_printf("\n");
}
