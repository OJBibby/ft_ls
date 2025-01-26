/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:41:18 by obibby            #+#    #+#             */
/*   Updated: 2025/01/26 19:42:38 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

void	expl_paths(char **paths, t_flags *flags);

int	path_exists(char *path)
{
	struct stat	buf;

	if (stat(path, &buf))
		return (0);
	return (1);
}

char	**str_array(int n)
{
	char	**arr;

	arr = ft_calloc(n + 1, sizeof(char *));
	if (!arr)
	{
		ft_printf("Memory allocation failed.\n");
		return (NULL);
	}
	return (arr);
}

int	count_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	free_array_exit(char **array)
{
	free_array(array);
	exit(1);
}

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

	lstat(*path1, &stats1);
	lstat(*path2, &stats2);
}

void	sort_array(char **paths, t_flags *flags)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (paths[i])
	{
		j = i + 1;
		while (paths[j])
		{
			if (flags->t)
				sort_by_time(&paths[i], &paths[j], flags);
			else if (flags->r && ft_strncmp(paths[i], paths[j],
					ft_strlen(paths[i]) + 1) < 0)
				swap(paths + i, paths + j);
			else if (ft_strncmp(paths[i], paths[j], ft_strlen(paths[i]) + 1) > 0)
				swap(paths + i, paths + j);
			j++;
		}
		i++;
	}
	return ;
}

int	add_path(char *path, char *dir, char **path_arr)
{
	int	i;

	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	i = count_array(path_arr);
	path_arr[i] = ft_strjoin(path, dir);
	if (!path_arr[i])
	{
		ft_printf("Memory allocation failed.\n");
		return (1);
	}
	return (0);
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

void	read_dir(char *path, char **new_paths, char **files, t_flags *flags)
{
	DIR				*cur_dir;
	struct dirent	*entry;
	int				i;

	cur_dir = opendir(path);
	entry = readdir(cur_dir);
	i = 0;
	while (entry)
	{
		if (!flags->a && entry->d_name[0] == '.')
		{
			entry = readdir(cur_dir);
			continue ;
		}
		files[i++] = ft_strdup(entry->d_name);
		if (flags->R && entry->d_type == 4)
		{
			if (add_path(path, entry->d_name, new_paths))
				return ;
		}
		entry = readdir(cur_dir);
	}
}

void	print_files(char **files, t_flags *flags)
{
	int	i;

	i = 0;
	if (flags->r)
	{
		i = count_array(files) - 1;
		while (i >= 0)
			ft_printf("%s	", files[i--]);
	}
	else
	{
		i = 0;
		while (files[i])
			ft_printf("%s	", files[i++]);
	}
	if (files[0])
		write(1, "\n", 1);
	free_array(files);
}

void	print_result(char **path, char **files, \
			char **new_paths, t_flags *flags)
{	
	ft_printf("%s:\n", path[0]);
	print_files(files, flags);
	if (path[1])
		write(1, "\n", 1);
	if (flags->R && new_paths[0])
	{
		sort_array(new_paths, flags->r);
		expl_paths(new_paths, flags);
		write(1, "\n", 1);
	}
}

void	expl_paths(char **paths, t_flags *flags)
{
	int				i;
	int				n;
	char			**new_paths;
	char			**files;

	i = 0;
	while (paths[i])
	{
		n = count_entries(paths[i]);
		new_paths = ft_calloc(n + 1, sizeof(char *));
		files = ft_calloc(n + 1, sizeof(char *));
		if (!new_paths || !files)
		{
			ft_printf("Memory allocation failed.\n");
			free_array(paths);
			return ;
		}
		read_dir(paths[i], new_paths, files, flags);
		sort_array(files, flags->r);
		print_result(paths + i, files, new_paths, flags);
		i++;
	}
	free_array(paths);
	return ;
}

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

int	assign_flags(t_flags *flags, char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'R')
			flags->R = 1;
		else if (str[i] == 'l')
			flags->l = 1;
		else if (str[i] == 'a')
			flags->a = 1;
		else if (str[i] == 'r')
			flags->r = 1;
		else if (str[i] == 't')
			flags->t = 1;
		else
		{
			ft_printf("ft_ls: invalid option -- %c\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	fill_path_arr(char **path, int argc, char **argv, t_flags *flags)
{
	int	i;
	int	x;

	i = 1;
	x = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-' || path[0])
		{
			assign_path(path, argv[i], x);
			x++;
		}
		else
		{
			if (assign_flags(flags, argv[i]))
			{
				free_array(path);
				exit(1);
			}
		}
		i++;
	}
}

char	**process_input(t_flags *flags, int argc, char **argv)
{
	char	**path;

	path = str_array(argc);
	if (!path)
		exit(1);
	fill_path_arr(path, argc, argv, flags);
	if (!path[0])
		assign_path(path, ".", 0);
	path = check_paths(path);
	sort_array(path, flags);
	return (path);
}

void	init_flags(t_flags *flags)
{
	flags->a = 0;
	flags->l = 0;
	flags->R = 0;
	flags->r = 0;
	flags->t = 0;
	return ;
}

int	main(int argc, char *argv[])
{
	t_flags	flags;
	char	**path;

	init_flags(&flags);
	path = process_input(&flags, argc, argv);
	expl_paths(path, &flags);
	return (0);
}
