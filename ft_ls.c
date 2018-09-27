/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 12:47:36 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/27 12:27:50 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_before(t_file **list, t_file *new)
{
	new->next = *list;
	*list = new;
}

void	put_list(t_flags *flags, int narg, t_file **flist, t_file **dlist)
{
	t_file	*head;

	merge_sort(flags, flist);
	print_list(flags, flist);
	if (*flist != NULL && narg++ > 1)
		ft_printf("\n");
	del_list(flags, flist);
	merge_sort(flags, dlist);
	head = *dlist;
	while (head != NULL)
	{
		if (narg > 1)
			ft_printf("%s:\n", head->path);
		start_list(flags, head->path);
		if (head->next != NULL)
			ft_printf("\n");
		head = head->next;
	}
	flags->R = 0;
	del_list(flags, dlist);
}

void	split_args(t_flags *flags, int *argc, int *i, char **argv)
{
	t_file	**flist;
	t_file	**dlist;
	t_file	*head;
	int		narg;

	if (!(flist = (t_file **)malloc(sizeof(t_file *))))
		return ;
	if (!(dlist = (t_file **)malloc(sizeof(t_file *))))
		return ;
	*flist = NULL;
	*dlist = NULL;
	narg = *argc - *i;
	while (*i < *argc)
	{
		head = file_new(flags, ft_strdup(argv[*i]), 1);
		if (S_ISDIR(head->stat->st_mode))
			add_before(dlist, head);
		else
			add_before(flist, head);
		*i = *i + 1;
	}
	put_list(flags, narg, flist, dlist);
	free(flist);
	free(dlist);
}

int		main(int argc, char **argv)
{
	int		i;
	t_flags	*flags;

	flags = flags_new();
	i = 1;
	while (i < argc && *argv[i] == '-')
	{
		if (get_flags(flags, argv[i]) != 0)
			return (-1);
		i++;
	}
	if (i >= argc)
		start_list(flags, ".");
	else
		split_args(flags, &argc, &i, argv);
	free(flags);
	return (0);
}
