/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 13:57:04 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/21 13:59:48 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

char	execution_mode(mode_t st_mode, mode_t mask)
{
	char	c;

	c = '-';
	if (st_mode & mask)
		c = 'x';
	if (mask == S_IXUSR && (st_mode & S_ISUID))
		c = (c == 'x') ? 's' : 'S';
	if (mask == S_IXGRP && (st_mode & S_ISGID))
		c = (c == 'x') ? 's' : 'S';
	if (mask == S_IXOTH && (st_mode & S_ISVTX))
		c = (c == 'x') ? 't' : 'T';
	return (c);
}
