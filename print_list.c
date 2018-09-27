/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:11:22 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/27 12:29:28 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

blkcnt_t	get_blkcnt(t_flags *flags, t_file **list)
{
	t_file		*head;
	blkcnt_t	blkcnt;

	head = *list;
	blkcnt = 0;
	while (head != NULL)
	{
		if (flags->a || *head->name != '.')
			blkcnt += head->stat->st_blocks;
		head = head->next;
	}
	return (blkcnt);
}

void		print_columns(t_flags *flags, t_file *file)
{
	ft_printf("%-*s", flags->name_width, file->name);
}

void		print_current(t_flags *flags, t_file *file)
{
	if (file->error)
		return ;
	if (flags->l)
		print_long(flags, file);
	else if (flags->one)
		ft_printf("%s\n", file->name);
	else
		print_columns(flags, file);
}

void		print_list(t_flags *flags, t_file **list)
{
	t_file	*head;

	head = *list;
	if (head == NULL)
		return ;
	while (head != NULL)
	{
		if (flags->a || *head->name != '.' || head->is_arg)
			print_current(flags, head);
		head = head->next;
	}
	if (!flags->l && !flags->one)
		ft_printf("\n");
}
