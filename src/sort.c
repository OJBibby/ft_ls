/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:32:39 by obibby            #+#    #+#             */
/*   Updated: 2025/01/28 21:33:22 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap(char **one, char **two)
{
	char	*temp;

	temp = one[0];
	one[0] = two[0];
	two[0] = temp;
}

void	sort_by_time(char **path1, char **path2, t_flags *flags)
{
	struct stat	stats1;
	struct stat	stats2;
	char		*temp;

	lstat(*path1, &stats1);
	lstat(*path2, &stats2);
	if (flags->r && stats1.st_mtime > stats2.st_mtime)
	{
		temp = *path1;
		*path1 = *path2;
		*path2 = temp;
	}
	else if (!flags->r && stats1.st_mtime < stats2.st_mtime)
	{
		temp = *path1;
		*path1 = *path2;
		*path2 = temp;
	}
}

void	sort_array(char **paths, t_flags *flags)
{
	int		i;
	int		j;

	i = 0;
	while (paths[i])
	{
		j = i + 1;
		while (paths[j])
		{
			if (flags->t)
				sort_by_time(paths + i, paths + j, flags);
			else if (flags->r && ft_strncmp(paths[i], paths[j],
					ft_strlen(paths[i]) + 1) < 0)
				swap(paths + i, paths + j);
			else if (!flags->r && ft_strncmp(paths[i], paths[j],
					ft_strlen(paths[i]) + 1) > 0)
				swap(paths + i, paths + j);
			j++;
		}
		i++;
	}
	return ;
}
