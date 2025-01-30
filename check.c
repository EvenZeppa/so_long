#include "so_long.h"

int check_valid_chars(char **map)
{
	int i, j;
	
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

int check_required_elements(char **map)
{
	int i, j;
	int count_p = 0, count_e = 0, count_c = 0;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P') count_p++;
			if (map[i][j] == 'E') count_e++;
			if (map[i][j] == 'C') count_c++;
			j++;
		}
		i++;
	}
	if (count_p != 1 || count_e != 1 || count_c < 1)
	{
		ft_printf("Error\nThe map must contain 1 P, 1 E, and at least 1 C.\n");
		return (0);
	}
	return (1);
}

int check_rectangle(char **map)
{
	int i = 0;
	int width = strlen(map[0]);

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

int check_walls(char **map)
{
	int i, j;
	int width = strlen(map[0]);
	int height = 0;

	while (map[height])
		height++;

	for (j = 0; j < width; j++)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
		{
			ft_printf("Error\nThe map must be surrounded by walls.\n");
			return (0);
		}
	}

	for (i = 0; i < height; i++)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
		{
			ft_printf("Error\nThe map must be surrounded by walls.\n");
			return (0);
		}
	}
	return (1);
}

int check_valid_path(char **map)
{
	int x, y, i, j;
	char **copy_map;

	for (y = 0; map[y]; y++)
		for (x = 0; map[y][x]; x++)
			if (map[y][x] == 'P')
				goto found;
found:

	copy_map = copy_map_function(map);
	flood_fill(copy_map, x, y);

	for (i = 0; copy_map[i]; i++)
		for (j = 0; copy_map[i][j]; j++)
			if (copy_map[i][j] == 'C' || copy_map[i][j] == 'E')
			{
				ft_printf("Error\nNo valid path to the exit or collectibles.\n");
				return (free_map(copy_map), 0);
			}

	return (free_map(copy_map), 1);
}
