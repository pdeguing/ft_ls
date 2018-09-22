/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_flags.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:56:16 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/22 10:26:53 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags		*flags_new(void)
{
	t_flags	*new;

	if (!(new = (t_flags *)malloc(sizeof(t_flags))))
		return (NULL);
	new->l = 0;
	new->R = 0;
	new->a = 0;
	new->r = 0;
	new->t = 0;
	new->h = 0;
	new->L = 0;
	new->n = 0;
	new->user_width = 0;
	new->grp_width = 0;
	new->max_size = 0;
	return (new);
}

int			flags_error(t_flags *flags, char c)
{
	free(flags);
	flags = NULL;
	ft_printf("ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-LRalrt] [file ...]\n");
	return (-1);
}

int			get_flags(t_flags *flags, char *arg)
{
	int		i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'l')
			flags->l = 1;
		else if (arg[i] == 'R')
			flags->R = 1;
		else if (arg[i] == 'a')
			flags->a = 1;
		else if (arg[i] == 'r')
			flags->r = 1;
		else if (arg[i] == 't')
			flags->t = 1;
		else if (arg[i] == 'h')
			flags->h = 1;
		else if (arg[i] == 'L')
			flags->L = 1;
		else if (arg[i] == 'n')
			flags->n = 1;
		else
			return (flags_error(flags, arg[i]));
	}
	return (0);
}
