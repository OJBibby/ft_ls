/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:32:39 by obibby            #+#    #+#             */
/*   Updated: 2025/01/29 12:52:14 by obibby           ###   ########.fr       */
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

int	str_compare(const char *str1, const char *str2, size_t n)
{
	size_t	x;
	int		cmp1;
	int		cmp2;

	x = 0;
	if (n == 0)
		return (0);
	while (str1[x] && str2[x] && x < n - 1)
	{
		if (str1[x] >= 'A' && str1[x] <= 'Z')
			cmp1 = str1[x] + 32;
		else
			cmp1 = str1[x];
		if (str2[x] >= 'A' && str2[x] <= 'Z')
			cmp2 = str2[x] + 32;
		else
			cmp2 = str2[x];
		if (cmp1 != cmp2)
			return (cmp1 - cmp2);
		x++;
	}
	return (str1[x] - str2[x]);
}

void	sort_by_value(char **path1, char **path2, t_flags *flags)
{
	int	cmp;

	cmp = str_compare(*path1, *path2, ft_strlen(*path1) + 1);
	if (flags->r && cmp < 0)
		swap(path1, path2);
	else if (!flags->r && cmp > 0)
		swap(path1, path2);
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
	else if (stats1.st_mtime == stats2.st_mtime)
		sort_by_value(path1, path2, flags);
}

void	sort_array(char **paths, t_flags *flags)
{
	int	i;
	int	j;

	i = 0;
	while (paths[i])
	{
		j = i + 1;
		while (paths[j])
		{
			if (flags->t)
				sort_by_time(paths + i, paths + j, flags);
			else
				sort_by_value(paths + i, paths + j, flags);
			j++;
		}
		i++;
	}
	return ;
}
