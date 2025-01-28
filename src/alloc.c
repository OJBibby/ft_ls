/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:30:13 by obibby            #+#    #+#             */
/*   Updated: 2025/01/28 21:39:15 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	free_file_info(t_file **file_info)
{
	int	i;

	i = 0;
	while (file_info[i])
		free(file_info[i++]);
	free(file_info);
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
