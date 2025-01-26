/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:14:43 by obibby            #+#    #+#             */
/*   Updated: 2025/01/26 19:45:38 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>

typedef struct s_flags
{
	int	R;
	int	l;
	int	a;
	int	r;
	int	t;
}	t_flags;

#endif