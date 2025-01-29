/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:41:18 by obibby            #+#    #+#             */
/*   Updated: 2025/01/29 12:51:10 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	expl_paths(char **paths, t_flags *flags)
{
	int				i;
	int				n;
	char			**new_paths;
	char			**files;

	i = 0;
	while (paths[i])
	{
		write(1, "\n", 1);
		ft_printf("%s:\n", paths[i]);
		n = count_entries(paths[i]);
		new_paths = str_array(n);
		files = str_array(n);
		if (!both_alloc(new_paths, files, paths))
			return (1);
		if (read_dir(paths[i], new_paths, files, flags))
			return (free_all(files, new_paths, paths));
		sort_array(files, flags);
		if (print_result(files, new_paths, flags))
			return (free_all(new_paths, paths, NULL));
		i++;
	}
	free_array(paths);
	return (0);
}

int	enter_recurs(char **paths, t_flags *flags)
{
	char	**new_paths;
	char	**files;
	int		n;

	n = count_entries(*paths);
	new_paths = ft_calloc(n + 1, sizeof(char *));
	files = ft_calloc(n + 1, sizeof(char *));
	if (!both_alloc(new_paths, files, NULL))
		return (1);
	if (read_dir(*paths, new_paths, files, flags))
		return (free_all(new_paths, files, NULL));
	sort_array(files, flags);
	if (print_result(files, new_paths, flags))
		return (1);
	return (0);
}

void	init_loop(char **paths, t_flags *flags)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (i > 0)
			write(1, "\n", 1);
		if (count_array(paths) > 1)
			ft_printf("%s:\n", paths[i]);
		if (enter_recurs(paths + i, flags))
			free_array_exit(paths);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_flags	flags;
	char	**path;

	set_flags(&flags);
	path = process_input(&flags, argc, argv);
	init_loop(path, &flags);
	free_array(path);
	return (0);
}
