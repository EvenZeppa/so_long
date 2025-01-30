#include "so_long.h"

char	*get_file_str(char *filename)
{
	int		fd;
	char	*file_str;
	char	*tmp_str;
	char	buf[2];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	file_str = malloc(1);
	file_str[0] = '\0';
	while (read(fd, buf, 1) > 0)
	{
		buf[1] = '\0';
		tmp_str = file_str;
		file_str = ft_strjoin(file_str, buf);
		free(tmp_str);
	}
	close(fd);
	return (file_str);
}

void flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F') 
		return;

	map[y][x] = 'F';

	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int	ft_strslen(char **strs)
{
	int i;

	for (i = 0; strs[i]; i++);
	return (i);
}

char **copy_map_function(char **map)
{
	int i;
	char **copy_map;

	copy_map = malloc(sizeof(char *) * (ft_strslen(map) + 1));
	for (i = 0; map[i]; i++)
		copy_map[i] = ft_strdup(map[i]);
	copy_map[i] = NULL;

	return (copy_map);
}

void	check_map(t_app *app, char *filename)
{
	char	*map_str = get_file_str(filename);
	if (!map_str)
	{
		ft_printf("Error\nUnable to open the file.\n");
		exit_program(app);
	}
	char	**map = ft_split(map_str, '\n');

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
