/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_flags.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:56:16 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/15 14:56:18 by pdeguing         ###   ########.fr       */
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
	return (new);
}

void	get_flags(t_flags *flags, char *arg)
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
		// ELSE FREE STRUCTURE AND DISPLAY ILLEGAL OPTION -arg[i] AND USAGE AND EXIT
		i++;
	}
}