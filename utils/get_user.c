/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 13:30:57 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/21 13:38:49 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

char	*get_user(t_flags *flags, uid_t st_uid)
{
	struct passwd	*user;

	user = getpwuid(st_uid);
	if (user == NULL || flags->n)
		return (ft_itoa(st_uid, 10));
	else
		return (ft_strdup(user->pw_name));
}
