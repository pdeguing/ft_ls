/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_xattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:03:49 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/27 11:03:51 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

char		get_xattr(char *path)
{
	acl_t	acl;

	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	else if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)) != NULL)
	{
		acl_free(acl);
		return ('+');
	}
	return (' ');
}
