/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:14:43 by obibby            #+#    #+#             */
/*   Updated: 2025/01/27 21:11:26 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>

typedef struct s_flags
{
	int	R;
	int	l;
	int	a;
	int	r;
	int	t;
}	t_flags;

typedef struct s_file
{
	char	*name;
	mode_t	mode;
	nlink_t	nlink;
	char	*user;
	char	*group;
	off_t	size;
	time_t	time;
}	t_file;

#endif