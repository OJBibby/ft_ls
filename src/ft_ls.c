/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:41:18 by obibby            #+#    #+#             */
/*   Updated: 2025/01/25 21:58:14 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

int	path_exists(char *path)
{
	struct stat buf;
	if (stat(path, &buf)) {
		return 0;
	}
	return 1;
}

int	count_array(char **array)
{
	int i;
	i = 0;

	while (array[i])
		i++;
	return i;
}

void	free_array(char **array)
{
	int i;
	i = 0;
	while (array[i]) {
		free(array[i]);
		i++;
	}
	free(array);
	return;
}

char	**check_paths(char **paths)
{
	char **valid_paths;
	int i;
	int	x;
	i = 0;
	x = 0;
	valid_paths = ft_calloc(count_array(paths) + 1, sizeof(char*));
	if (!valid_paths) {
		ft_printf("Memory allocation failed.\n");
		free_array(paths);
		exit(1);
	}
	while (paths[i]) {
		if (!path_exists(paths[i])) {
			ft_printf("ft_ls: %s: No such file or directory\n", paths[i]);
		}
		else {
			valid_paths[x] = ft_strdup(paths[i]);
			if (!valid_paths[x]) {
				ft_printf("Memory allocation failed.\n");
				free_array(paths);
				free_array(valid_paths);
				exit(1);
			}
			x++;
		}
		i++;
	}
	return valid_paths;
}

void assign_path(char **path, char *str, int i)
{
	path[i] = ft_strdup(str);
	if (!path[i]) {
		ft_printf("Memory allocation failed.\n");
		free_array(path);
		exit(1);
	}
}

int	assign_flags(t_flags flags, char *str)
{
	int	i;
	i = 1;
	while (str[i]) {
		switch (str[i]) {
			case 'R':
				flags.R = 1;
				break;
			case 'l':
				flags.l = 1;
				break;
			case 'a':
				flags.a = 1;
				break;
			case 'r':
				flags.r = 1;
				break;
			case 't':
				flags.t = 1;
				break;
			default:
				ft_printf("ft_ls: invalid option -- %c\n", str[i]);
				return 1;
		}
		i++;
	}
	return 0;
}

char	**process_input(t_flags flags, int argc, char **argv)
{
	char **path;
	path = ft_calloc(argc + 1, sizeof(char*));
	if (!path) {
		ft_printf("Memory allocation failed.\n");
		exit(1);
	}
	int i = 1;
	int x = 0;
	while (i < argc) {
		if (argv[i][0] != '-') {
			assign_path(path, argv[i], x);
			x++;
		}
		else {
			if (assign_flags(flags, argv[i])) {
				free_array(path);
				exit(1);
			}
		}
		i++;
	}
	path = check_paths(path);
	return path;
}

int	main(int argc, char *argv[])
{
	t_flags flags = {0};
	char	**path;
	path = process_input(flags, argc, argv);
	free_array(path);
	return 0;
}