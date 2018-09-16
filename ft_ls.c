/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 12:47:36 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/15 16:39:10 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** We check for flags specifiers in the argument and create a structure to hold
** the flags if any.
**
** Then we will list the current directory unless there is any name specified
** as argument.
**
** We need a way to know if we have to print the name of the first directory listed
** It is the case only if if we have more than 1 argument and if there is not error
*/


int		main(int argc, char **argv)
{
	int		i;
	t_flags	*flags;

	flags = flags_new();
	i = 1;
	while (i < argc && *argv[i] == '-')
	{
		get_flags(flags, argv[i]);
		i++;
	}
	if (i >= argc)
		start_list(flags, ".");
	while (i < argc)
	{
		start_list(flags, argv[i]);
		i++;
	}
	return (0);
}
