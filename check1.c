/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:23:57 by ezeppa            #+#    #+#             */
/*   Updated: 2025/01/30 19:47:08 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	find_player_position(char **map, int *x, int *y)
{
	*y = 0;
	while (map[*y])
	{
		*x = 0;
		while (map[*y][*x])
		{
			if (map[*y][*x] == 'P')
				return (1);
			(*x)++;
		}
		(*y)++;
	}
	return (0);
}

int	check_collectibles_and_exit(char **copy_map)
{
	int	i;
	int	j;

	i = 0;
	while (copy_map[i])
	{
		j = 0;
		while (copy_map[i][j])
		{
			if (copy_map[i][j] == 'C' || copy_map[i][j] == 'E')
			{
				ft_printf
					("Error\nNo valid path to the exit or collectibles.\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_valid_path(char **map)
{
	int		x;
	int		y;
	char	**copy_map;

	if (!find_player_position(map, &x, &y))
		return (0);
	copy_map = copy_map_function(map);
	flood_fill(copy_map, x, y);
	if (check_collectibles_and_exit(copy_map) == 0)
	{
		free_map(copy_map);
		return (0);
	}
	free_map(copy_map);
	return (1);
}
