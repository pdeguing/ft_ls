/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 13:30:05 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/21 13:30:48 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

char	*get_name(char *path)
{
	char	*name;
	int		i;

	i = ft_strlen(path) - 1;
	while (i > 0 && path[i] == '/')
		i--;
	while (i >= 0 && path[i] != '/')
		i--;
	name = ft_strdup(path + i + 1);
	return (name);
}
