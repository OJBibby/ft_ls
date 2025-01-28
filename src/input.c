/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:20:41 by obibby            #+#    #+#             */
/*   Updated: 2025/01/28 21:26:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	assign_flags(t_flags *flags, char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'R')
			flags->rec = 1;
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

void	check_args(char **path, int argc, char **argv, t_flags *flags)
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
	check_args(path, argc, argv, flags);
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
	flags->rec = 0;
	flags->r = 0;
	flags->t = 0;
	return ;
}
