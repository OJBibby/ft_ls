/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:30:13 by obibby            #+#    #+#             */
/*   Updated: 2025/01/29 12:51:47 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	free_all(char **arr1, char **arr2, char **arr3)
{
	if (arr1)
		free_array(arr1);
	if (arr2)
		free_array(arr2);
	if (arr3)
		free_array(arr3);
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
