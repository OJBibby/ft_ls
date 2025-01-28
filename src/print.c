/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:35:36 by obibby            #+#    #+#             */
/*   Updated: 2025/01/28 21:39:55 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_mod_time(time_t *t)
{
	char	*time_str;
	int		i;

	time_str = ctime(t);
	i = 4;
	while (time_str[i] && i < 16)
		write(1, &time_str[i++], 1);
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
		detailed_info(files);
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
