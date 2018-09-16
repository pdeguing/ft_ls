/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 12:48:15 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/15 19:45:30 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h" 
# include "dirent.h"
# include <sys/stat.h>
# include <stdlib.h>
# include <time.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>

/*
** Flags management
*/

typedef struct			s_flags
{
	int					l;
	int					R;
	int					a;
	int					r;
	int					t;
}						t_flags;

t_flags					*flags_new(void);
void					get_flags(t_flags *flags, char *arg);

/*
** Linked list to store files informations
**
** We can ether store the differents structs into one
** or just store the relevant data into our own struct
*/

typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct dirent	t_dirent;

typedef struct			s_file
{
	char				*f_name;
	t_stat				stat;
	t_passwd			*user;
	t_group				*group;
	int					error;

	struct s_file		*next;
}						t_file;

t_file					*file_new(char *name);

/*
** Main functions
*/

void					print_list(t_flags *flags, t_file **file);
void					sort_list(t_flags *flags, t_file **head);
void					start_list(t_flags *flags, char *name);

#endif
