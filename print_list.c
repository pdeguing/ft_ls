/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:11:22 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/15 19:43:33 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_current(t_flags *flags, t_file *file)
{
	if (flags->l)
	{
		// PRINT LONG
	}
	else
	{
		// PRINT DEFAULT
		ft_printf("%s\n", file->f_name);
	}
}

void	print_list(t_flags *flags, t_file **file)
{
	t_file	*tmp;
	t_file	*head;

	head = *file;
	while (head)
	{
		if (flags->a || *head->f_name != '.')
			print_current(flags, head);
		tmp = head->next;
		if (!S_ISDIR(head->stat.st_mode))
		{
			// DEL
		}
		head = tmp;
	}
}
