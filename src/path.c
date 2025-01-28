/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:28:06 by obibby            #+#    #+#             */
/*   Updated: 2025/01/28 21:29:30 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_valid_paths(char **paths, char **valid_paths)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (paths[i])
	{
		if (!path_exists(paths[i]))
			ft_printf("ft_ls: %s: No such file or directory\n", paths[i]);
		else
		{
			valid_paths[x] = ft_strdup(paths[i]);
			if (!valid_paths[x])
			{
				ft_printf("Memory allocation failed.\n");
				free_array(paths);
				free_array_exit(valid_paths);
			}
			x++;
		}
		i++;
	}
}

char	**check_paths(char **paths)
{
	char	**valid_paths;

	valid_paths = str_array(count_array(paths) + 1);
	if (!valid_paths)
		free_array_exit(paths);
	get_valid_paths(paths, valid_paths);
	free_array(paths);
	return (valid_paths);
}

void	assign_path(char **path, char *str, int i)
{
	path[i] = ft_strdup(str);
	if (!path[i])
	{
		ft_printf("Memory allocation failed.\n");
		free_array(path);
		exit(1);
	}
}
