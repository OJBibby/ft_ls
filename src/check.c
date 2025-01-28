/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:37:39 by obibby            #+#    #+#             */
/*   Updated: 2025/01/28 21:39:21 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	path_exists(char *path)
{
	struct stat	buf;

	if (stat(path, &buf))
		return (0);
	return (1);
}

int	count_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	count_entries(char *str)
{
	int				n;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(str);
	n = 0;
	entry = readdir(dir);
	while (entry)
	{
		n++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (n);
}
