/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:41:18 by obibby            #+#    #+#             */
/*   Updated: 2025/01/27 23:21:52 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"
#include <stdio.h>

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
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
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
	char		*temp;

	lstat(*path1, &stats1);
	lstat(*path2, &stats2);
	if (flags->r && stats1.st_mtime > stats2.st_mtime)
	{
		temp = *path1;
		*path1 = *path2;
		*path2 = temp;
	}
	else if (stats1.st_mtime < stats2.st_mtime)
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
			else if (ft_strncmp(paths[i], paths[j],
					ft_strlen(paths[i]) + 1) > 0)
				swap(paths + i, paths + j);
			j++;
		}
		i++;
	}
	return ;
}

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

	cur_dir = opendir(path);
	entry = readdir(cur_dir);
	while (entry)
	{
		if (flags->a || entry->d_name[0] != '.')
		{
			if (add_path(path, entry->d_name, files))
				break ;
			if (flags->R && entry->d_type == 4 && entry->d_name[0] != '.')
			{
				if (add_path(path, entry->d_name, new_paths))
					break ;
			}
		}
		entry = readdir(cur_dir);
	}
	closedir(cur_dir);
}

void	detailed_print_rev(char **file)
{
	int	i;

	i = count_array(file) - 1;
	while (i >= 0)
	{
		i--;
	}
}

void	print_mod_time(time_t *t)
{
	char	*time_str;
	int		i;

	time_str = ctime(t);
	i = 4;
	while (time_str[i] && i < 16)
		write(1, &time_str[i++], 1);
}

void	print_perm_usr(mode_t perms)
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

void	print_perm_grp(mode_t perms)
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

void	print_perm_oth(mode_t perms)
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

void	print_permissions(mode_t perms)
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

void	detailed_print(t_file **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		print_permissions(file[i]->mode);
		ft_printf("%2d ", file[i]->nlink);
		ft_printf("%6s ", file[i]->user);
		ft_printf("%6s ", file[i]->group);
		ft_printf("%6d ", file[i]->size);
		print_mod_time(&file[i]->time);
		ft_printf(" %s", ft_strrchr(file[i]->name, '/') + 1);
		i++;
		if (file[i])
			write(1, "\n", 1);
	}
}

void	free_file_info(t_file **file_info)
{
	int	i;

	i = 0;
	while (file_info[i])
		free(file_info[i++]);
	free(file_info);
}

int	gather_info(char **file, t_file **file_info, int i)
{
	struct stat	file_stat;
	int			total;

	file_info[i] = ft_calloc(1, sizeof(t_file));
	if (!file_info[i])
		return (-1);
	lstat(file[i], &file_stat);
	file_info[i]->name = file[i];
	file_info[i]->mode = file_stat.st_mode;
	file_info[i]->nlink = file_stat.st_nlink;
	file_info[i]->user = getpwuid(file_stat.st_uid)->pw_name;
	file_info[i]->group = getgrgid(file_stat.st_gid)->gr_name;
	file_info[i]->size = file_stat.st_size;
	file_info[i]->time = file_stat.st_mtime;
	total = 0;
	if (!S_ISDIR(file_stat.st_mode))
	{
		total += 8 * (file_stat.st_size / 4096);
		if (file_stat.st_size % 4096)
			total += 8;
	}
	return (total);
}

void	detailed_info(char **file)
{
	int			i;
	t_file		**file_info;
	int			total;
	int			ret;

	i = 0;
	total = 0;
	file_info = ft_calloc(count_array(file) + 1, sizeof(t_file *));
	if (!file_info)
		return ;
	while (file[i])
	{
		ret = gather_info(file, file_info, i);
		if (ret < 0)
		{
			free_file_info(file_info);
			return ;
		}
		total += ret;
		i++;
	}
	ft_printf("total %d\n", total);
	detailed_print(file_info);
	free_file_info(file_info);
}

void	print_files(char **files, t_flags *flags)
{
	int	i;

	i = 0;
	if (flags->l)
	{
		detailed_info(files);
	}
	else if (flags->r)
	{
		i = count_array(files) - 1;
		while (i >= 0)
			ft_printf("%s	", ft_strrchr(files[i--], '/') + 1);
	}
	else
	{
		i = 0;
		while (files[i])
			ft_printf("%s	", ft_strrchr(files[i++], '/') + 1);
	}
	if (files[0])
		write(1, "\n", 1);
	free_array(files);
}

void	print_result(char **files, \
			char **new_paths, t_flags *flags)
{
	print_files(files, flags);
	if (flags->R && new_paths[0])
	{
		sort_array(new_paths, flags);
		expl_paths(new_paths, flags);
	}
	else
		free(new_paths);
}

int	both_alloc(char **arr1, char **arr2)
{
	if (!arr1 && !arr2)
	{
		ft_printf("Memory allocation failed.\n");
		return (0);
	}
	else if (!arr1)
	{
		ft_printf("Memory allocation failed.\n");
		free(arr2);
		return (0);
	}
	else if (!arr2)
	{
		ft_printf("Memory allocation failed.\n");
		free(arr1);
		return (0);
	}
	return (1);
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
		write(1, "\n", 1);
		ft_printf("%s:\n", paths[i]);
		n = count_entries(paths[i]);
		new_paths = ft_calloc(n + 1, sizeof(char *));
		files = ft_calloc(n + 1, sizeof(char *));
		if (!both_alloc(new_paths, files))
			break ;
		read_dir(paths[i], new_paths, files, flags);
		sort_array(files, flags);
		print_result(files, new_paths, flags);
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

void	set_flags(t_flags *flags)
{
	flags->a = 0;
	flags->l = 0;
	flags->R = 0;
	flags->r = 0;
	flags->t = 0;
	return ;
}

void	enter_recurs(char **paths, t_flags *flags)
{
	char	**new_paths;
	char	**files;
	int		n;

	n = count_entries(*paths);
	new_paths = ft_calloc(n + 1, sizeof(char *));
	files = ft_calloc(n + 1, sizeof(char *));
	if (!both_alloc(new_paths, files))
		return ;
	read_dir(*paths, new_paths, files, flags);
	sort_array(files, flags);
	print_result(files, new_paths, flags);
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
		enter_recurs(paths + i, flags);
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
