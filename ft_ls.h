/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 12:48:15 by pdeguing          #+#    #+#             */
/*   Updated: 2018/09/21 14:53:40 by pdeguing         ###   ########.fr       */
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
# include <stdio.h>
# include <errno.h>
# define SIX_MONTHS 15778463
# define IS_RECENT(timedif) (timedif < SIX_MONTHS && timedif * -1 < SIX_MONTHS)
# define MAJOR(dev) ((int)(((unsigned int) (dev) >> 24) & 0xff))
# define MINOR(dev) ((int)((dev) & 0xff))
# define R cr
# define L cl
# define SHOW_INV (*(*list)->name != '.' || flags->a)
# define NOT_PARENT *((*list)->name + 1) && *((*list)->name + 1) != '.'
# define NOT_DOT *((*list)->name + 1) != '/'
# define RECURSE_DIR S_ISDIR((*list)->stat->st_mode) && flags->R

/*
** Flags management
*/

typedef struct			s_flags
{
	int					l;
	int					cr;
	int					a;
	int					r;
	int					t;
	int					h;
	int					cl;
	int					n;
	int					user_width;
	int					grp_width;
	int					max_size;
}						t_flags;

t_flags					*flags_new(void);
int						get_flags(t_flags *flags, char *arg);

/*
** Linked list to store files informations.
**
** We can ether store the differents structs into one
** or just store the relevant data into our own struct.
** We chose to store each struct by itself for now as the relevant data
** could vary depending on our need.
*/

typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct dirent	t_dirent;

typedef struct			s_file
{
	char				*path;
	char				*name;
	t_stat				*stat;
	char				*user;
	char				*grp;
	char				*link;
	int					is_arg;
	int					error;

	struct s_file		*next;
}						t_file;

/*
** Utils
*/

char					*get_grp(t_flags *flags, gid_t st_gid);
char					*get_name(char *path);
void					get_stat(t_flags *flags, t_file *file);
char					*get_user(t_flags *flags, uid_t st_uid);
char					*get_link(t_file *file);
char					execution_mode(mode_t st_mode, mode_t mask);

t_file					*file_new(t_flags *flags, char *name, int is_arg);

/*
** Main functions
*/

blkcnt_t				get_blkcnt(t_flags *flags, t_file **list);
void					del_node(t_file **list);
void					del_list(t_flags *flags, t_file **list);
void					print_long(t_flags *flags, t_file *file);
void					print_list(t_flags *flags, t_file **file);
void					merge_sort(t_flags *flags, t_file **head);
void					start_list(t_flags *flags, char *name);

#endif
