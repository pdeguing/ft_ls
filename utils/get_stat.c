/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 13:32:06 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/21 13:32:42 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

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
