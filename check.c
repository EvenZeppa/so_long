/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:23:57 by ezeppa            #+#    #+#             */
/*   Updated: 2025/01/30 19:47:36 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_valid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' &&
				map[i][j] != '1' &&
				map[i][j] != 'C' &&
				map[i][j] != 'E' &&
				map[i][j] != 'P')
			{
				ft_printf("Error\nInvalid character in the map.\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_required_elements(char **map)
{
	int	count_pe;
	int	count_c;
	int	i;
	int	j;

	count_pe = 0;
	count_c = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'P')
				count_pe++;
			if (map[i][j] == 'E')
				count_pe++;
			if (map[i][j] == 'C')
				count_c++;
		}
	}
	if (count_pe != 2 || count_c < 1)
		return (ft_printf
			("Error\nThe map must contain 1 P, 1 E, and at least 1 C.\n"), 0);
	return (1);
}

int	check_rectangle(char **map)
{
	int	i;
	int	width;

	i = 0;
	width = ft_strlen(map[0]);
	while (map[i])
	{
		if ((int)strlen(map[i]) != width)
		{
			ft_printf("Error\nThe map must be rectangular.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_walls(char **map)
{
	int	i;
	int	j;
	int	width;
	int	height;

	width = strlen(map[0]);
	height = 0;
	while (map[height])
		height++;
	j = -1;
	while (++j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (ft_printf
				("Error\nThe map must be surrounded by walls.\n"), 0);
	}
	i = -1;
	while (++i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (ft_printf
				("Error\nThe map must be surrounded by walls.\n"), 0);
	}
	return (1);
}

void	check_map(t_app *app, char *filename)
{
	char	*map_str;
	char	**map;

	map_str = get_file_str(filename);
	if (!map_str)
	{
		ft_printf("Error\nUnable to open the file.\n");
		exit_program(app);
	}
	map = ft_split(map_str, '\n');
	if (!check_valid_chars(map)
		|| !check_required_elements(map)
		|| !check_rectangle(map)
		|| !check_walls(map)
		|| !check_valid_path(map))
	{
		free(map_str);
		free_map(map);
		exit_program(app);
	}
	free(map_str);
	free_map(map);
}
