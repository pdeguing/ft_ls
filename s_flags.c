/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_flags.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:56:16 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/20 19:39:28 by pdeguing         ###   ########.fr       */
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

void		get_flags(t_flags *flags, char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == 'l')
			flags->l = 1;
		if (arg[i] == 'R')
			flags->R = 1;
		if (arg[i] == 'a')
			flags->a = 1;
		if (arg[i] == 'r')
			flags->r = 1;
		if (arg[i] == 't')
			flags->t = 1;
		if (arg[i] == 'h')
			flags->h = 1;
		if (arg[i] == 'L')
			flags->L = 1;
		if (arg[i] == 'n')
			flags->n = 1;
		// ELSE FREE STRUCTURE AND DISPLAY ILLEGAL OPTION -arg[i] AND USAGE AND EXIT
		i++;
	}
}
