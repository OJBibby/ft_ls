/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:34:23 by obibby            #+#    #+#             */
/*   Updated: 2025/01/29 11:38:24 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_perm_usr(unsigned int perms)
{
	if (perms & S_IRUSR)
		write(1, "r", 1);
	else
		write(1, "-", 1);
	if (perms & S_IWUSR)
		write(1, "w", 1);
	else
		write(1, "-", 1);
	if (perms & S_IXUSR)
		write(1, "x", 1);
	else
		write(1, "-", 1);
}

void	print_perm_grp(unsigned int perms)
{
	if (perms & S_IRGRP)
		write(1, "r", 1);
	else
		write(1, "-", 1);
	if (perms & S_IWGRP)
		write(1, "w", 1);
	else
		write(1, "-", 1);
	if (perms & S_IXGRP)
		write(1, "x", 1);
	else
		write(1, "-", 1);
}

void	print_perm_oth(unsigned int perms)
{
	if (perms & S_IROTH)
		write(1, "r", 1);
	else
		write(1, "-", 1);
	if (perms & S_IWOTH)
		write(1, "w", 1);
	else
		write(1, "-", 1);
	if (perms & S_IXOTH)
		write(1, "x", 1);
	else
		write(1, "-", 1);
}

void	print_permissions(unsigned int perms)
{
	if (S_ISDIR(perms))
		write(1, "d", 1);
	else
		write(1, "-", 1);
	print_perm_usr(perms);
	print_perm_grp(perms);
	print_perm_oth(perms);
	write(1, " ", 1);
}
