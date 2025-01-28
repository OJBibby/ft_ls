/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:14:43 by obibby            #+#    #+#             */
/*   Updated: 2025/01/28 21:52:08 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>

typedef struct s_flags
{
	int	rec;
	int	l;
	int	a;
	int	r;
	int	t;
}	t_flags;

typedef struct s_file
{
	char	*name;
	mode_t	mode;
	nlink_t	nlink;
	char	*user;
	char	*group;
	off_t	size;
	time_t	time;
}	t_file;

void	free_array(char **array);
char	**process_input(t_flags *flags, int argc, char **argv);
void	set_flags(t_flags *flags);
int		count_array(char **array);
void	print_result(char **files, char **new_paths, t_flags *flags);
void	sort_array(char **paths, t_flags *flags);
void	read_dir(char *path, char **new_paths, char **files, t_flags *flags);
int		both_alloc(char **arr1, char **arr2);
int		count_entries(char *str);
char	**check_paths(char **paths);
void	assign_path(char **path, char *str, int i);
char	**str_array(int n);
void	free_array_exit(char **array);
int		path_exists(char *path);
void	free_file_info(t_file **file_info);
void	print_permissions(mode_t perms);
void	print_files(char **files, t_flags *flags);
void	expl_paths(char **paths, t_flags *flags);

#endif