/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:07:43 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/15 19:43:24 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*sorted_merge(t_file *a, t_file *b)
{
	t_file	*result;

	result = NULL;
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (ft_strcmp(a->f_name, b->f_name) < 0)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
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
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
}

void	merge_sort(t_file **ref)
{
	t_file	*head;
	t_file	*a;
	t_file	*b;

	head = *ref;
	if (!head || !head->next)
		return ;
	split_list(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*ref = sorted_merge(a, b);
}

void	sort_list(t_flags *flags, t_file **ref)
{
	// SORT ALPHABETICALLY
	if (!flags->t)
		merge_sort(ref);
}
