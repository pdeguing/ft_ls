/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:07:43 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/20 09:41:15 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_cmp(t_flags *flags, t_file *a, t_file *b)
{
	int		ret;

	if (flags->t)
		ret = b->stat->st_mtimespec.tv_sec - a->stat->st_mtimespec.tv_sec;
	else
		ret = ft_strcmp(a->path, b->path);
	return (ret * ((flags->r) ? -1 : 1));
}

t_file	*sorted_merge(t_flags *flags, t_file *a, t_file *b)
{
	t_file	*result;

	result = NULL;
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (get_cmp(flags, a, b) < 0)
	{
		result = a;
		result->next = sorted_merge(flags, a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(flags, a, b->next);
	}
	return (result);
}

/*
** We move 2 heads within the list, one twice as fast as the other one
** so when the fast one reaches the end, the slow one is just before the middle
*/

void	split_list(t_file *head, t_file **a, t_file **b)
{
	t_file	*fast;
	t_file	*slow;

	slow = head;
	fast = head->next;
	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
}

void	merge_sort(t_flags *flags, t_file **list)
{
	t_file	*head;
	t_file	*a;
	t_file	*b;

	head = *list;
	if (head == NULL || head->next == NULL)
		return ;
	split_list(head, &a, &b);
	merge_sort(flags, &a);
	merge_sort(flags, &b);
	*list = sorted_merge(flags, a, b);
}
