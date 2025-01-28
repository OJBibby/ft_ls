/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:40:48 by obibby            #+#    #+#             */
/*   Updated: 2025/01/28 21:41:41 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	add_path(char *path, char *dir, char **path_arr)
{
	int		i;

	i = count_array(path_arr);
	if (path[ft_strlen(path) - 1] != '/')
	{
		path = ft_strjoin(path, "/");
		path_arr[i] = ft_strjoin(path, dir);
		free(path);
	}
	else
		path_arr[i] = ft_strjoin(path, dir);
	if (!path_arr[i])
	{
		ft_printf("Memory allocation failed.\n");
		return (1);
	}
	return (0);
}

void	read_dir(char *path, char **new_paths, char **files, t_flags *flags)
{
	DIR				*cur_dir;
	struct dirent	*entry;

	cur_dir = opendir(path);
	entry = readdir(cur_dir);
	while (entry)
	{
		if (flags->a || entry->d_name[0] != '.')
		{
			if (add_path(path, entry->d_name, files))
				break ;
			if (flags->rec && entry->d_type == 4 && entry->d_name[0] != '.')
			{
				if (add_path(path, entry->d_name, new_paths))
					break ;
			}
		}
		entry = readdir(cur_dir);
	}
	closedir(cur_dir);
}

void	print_result(char **files, \
			char **new_paths, t_flags *flags)
{
	print_files(files, flags);
	if (flags->rec && new_paths[0])
	{
		sort_array(new_paths, flags);
		expl_paths(new_paths, flags);
	}
	else
		free(new_paths);
}
