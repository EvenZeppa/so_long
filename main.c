#include "libft.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

typedef enum e_cell_type
{
	CELL_EMPTY = '0',
	CELL_WALL = '1'
}	t_cell_type;

typedef enum e_entity_type
{
	ENTITY_PLAYER = 'P',
	ENTITY_COLLECTIBLE = 'C',
	ENTITY_EXIT = 'E'
}	t_entity_type;

typedef struct s_img_xpm
{
	void	*img;
	int		width;
	int		height;
}	t_img_xpm;

typedef struct s_entity
{
	t_entity_type	type;
	t_img_xpm		*a1;
	t_img_xpm		*a2;
	int				x;
	int				y;
}	t_entity;

typedef struct s_cell
{
	t_cell_type	type;
	int			x;
	int			y;
}	t_cell;

typedef struct s_map
{
	t_cell	**cells;
	int		width;
	int		height;
}	t_map;

typedef struct s_imgs
{
	t_img_xpm	empty;
	t_img_xpm	player_a1;
	t_img_xpm	player_a2;
	t_img_xpm	wall;
	t_img_xpm	collectible;
	t_img_xpm	exit;
}	t_imgs;

typedef struct s_app
{
	void		*mlx;
	void		*mlx_win;

	t_map		map;
	t_imgs		imgs;

	t_entity	*player;
	t_entity	*exit;
	int			nb_collectibles;
	t_entity	**collectibles;
	int			nb_moves;
}	t_app;

int	exit_program(t_app *app)
{
	mlx_destroy_image(app->mlx, app->imgs.empty.img);
	mlx_destroy_image(app->mlx, app->imgs.player_a1.img);
	mlx_destroy_image(app->mlx, app->imgs.player_a2.img);
	mlx_destroy_image(app->mlx, app->imgs.wall.img);
	mlx_destroy_image(app->mlx, app->imgs.collectible.img);
	mlx_destroy_image(app->mlx, app->imgs.exit.img);
	if (app->mlx_win)
		mlx_destroy_window(app->mlx, app->mlx_win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	for (int i = 0; i < app->map.height; i++)
		free(app->map.cells[i]);
	free(app->map.cells);
	free(app->player);
	free(app->exit);
	for (int i = 0; i < 100; i++)
		if (app->collectibles[i])
			free(app->collectibles[i]);
	free(app->collectibles);
	exit(0);
	return (0);
}

void	init_imgs(t_app *app)
{
	app->imgs.empty.img = mlx_xpm_file_to_image(app->mlx, "images/empty.xpm", &app->imgs.empty.width, &app->imgs.empty.height);
	app->imgs.player_a1.img = mlx_xpm_file_to_image(app->mlx, "images/player_a1.xpm", &app->imgs.player_a1.width, &app->imgs.player_a1.height);
	app->imgs.player_a2.img = mlx_xpm_file_to_image(app->mlx, "images/player_a2.xpm", &app->imgs.player_a2.width, &app->imgs.player_a2.height);
	app->imgs.wall.img = mlx_xpm_file_to_image(app->mlx, "images/wall.xpm", &app->imgs.wall.width, &app->imgs.wall.height);
	app->imgs.collectible.img = mlx_xpm_file_to_image(app->mlx, "images/collectible.xpm", &app->imgs.collectible.width, &app->imgs.collectible.height);
	app->imgs.exit.img = mlx_xpm_file_to_image(app->mlx, "images/exit.xpm", &app->imgs.exit.width, &app->imgs.exit.height);
}

void	add_collectible(t_app *app, int x, int y)
{
	t_entity	*collectible;
	int			i;

	i = 0;
	while (app->collectibles[i])
		i++;
	collectible = malloc(sizeof(t_entity));
	collectible->type = ENTITY_COLLECTIBLE;
	collectible->a1 = &app->imgs.collectible;
	collectible->a2 = NULL;
	collectible->x = x;
	collectible->y = y;
	app->collectibles[i] = collectible;
	app->collectibles[i + 1] = NULL;
}

void	add_player(t_app *app, int x, int y)
{
	app->player->type = ENTITY_PLAYER;
	app->player->a1 = &app->imgs.player_a1;
	app->player->a2 = &app->imgs.player_a2;
	app->player->x = x;
	app->player->y = y;
}

void	add_exit(t_app *app, int x, int y)
{
	app->exit->type = ENTITY_EXIT;
	app->exit->a1 = &app->imgs.exit;
	app->exit->a2 = NULL;
	app->exit->x = x;
	app->exit->y = y;
}

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

void	init_map(t_app *app, char *filename)
{
	char *map_str = get_file_str(filename);
	if (!map_str)
	{
		ft_printf("Error\nUnable to open the file.\n");
		exit_program(app);
	}
	char **split = ft_split(map_str, '\n');

	app->map.width = ft_strlen(split[0]);
	app->map.height = 0;
	for (int i = 0; split[i]; i++)
		app->map.height++;
	app->map.cells = malloc(app->map.height * sizeof(t_cell *));
	for (int i = 0; i < app->map.height; i++)
	{
		app->map.cells[i] = malloc(app->map.width * sizeof(t_cell));
		for (int j = 0; j < app->map.width; j++)
		{
			if (split[i][j] == CELL_WALL)
				app->map.cells[i][j].type = CELL_WALL;
			else
				app->map.cells[i][j].type = CELL_EMPTY;
			if (split[i][j] == ENTITY_PLAYER)
				add_player(app, j, i);
			else if (split[i][j] == ENTITY_COLLECTIBLE)
			{
				add_collectible(app, j, i);
				app->nb_collectibles++;
			}
			else if (split[i][j] == ENTITY_EXIT)
				add_exit(app, j, i);
			app->map.cells[i][j].x = j;
			app->map.cells[i][j].y = i;
		}
		free(split[i]);
	}
	free(split);
	free(map_str);
}

void	refresh_screen(t_app *app)
{
	mlx_destroy_window(app->mlx, app->mlx_win);
	app->mlx_win = mlx_new_window(app->mlx, app->map.width * 32, app->map.height * 32, "so_long");
}

void	init_app(t_app *app)
{
	app->mlx = mlx_init();
	app->mlx_win = mlx_new_window(app->mlx, 800, 800, "so_long");
	
	app->nb_moves = 0;
	app->nb_collectibles = 0;
	app->collectibles = malloc(sizeof(t_entity *) * 100);
	for (int i = 0; i < 100; i++)
		app->collectibles[i] = NULL;
	app->player = malloc(sizeof(t_entity));
	app->exit = malloc(sizeof(t_entity));
	init_imgs(app);
}

void	draw_map(t_app *app)
{
	mlx_clear_window(app->mlx, app->mlx_win);
	for (int i = 0; i < app->map.height; i++)
	{
		for (int j = 0; j < app->map.width; j++)
		{
			if (app->map.cells[i][j].type == CELL_WALL)
				mlx_put_image_to_window(app->mlx, app->mlx_win, app->imgs.wall.img, j * 32, i * 32);
			else
			{
				mlx_put_image_to_window(app->mlx, app->mlx_win, app->imgs.empty.img, j * 32, i * 32);
			}
		}
	}
}

void	draw_entities(t_app *app)
{
	static int time_anim = 0;

	mlx_put_image_to_window(app->mlx, app->mlx_win, app->exit->a1->img, app->exit->x * 32, app->exit->y * 32);
	for (int i = 0; i < 100; i++)
	{
		if (app->collectibles[i])
			mlx_put_image_to_window(app->mlx, app->mlx_win, app->collectibles[i]->a1->img, app->collectibles[i]->x * 32, app->collectibles[i]->y * 32);
	}
	if (time_anim % 10 < 5)
		mlx_put_image_to_window(app->mlx, app->mlx_win, app->player->a2->img, app->player->x * 32, app->player->y * 32);
	else
		mlx_put_image_to_window(app->mlx, app->mlx_win, app->player->a1->img, app->player->x * 32, app->player->y * 32);
	time_anim++;
}

void	move_entity(t_app *app, t_entity *entity, int x, int y)
{
	if (app->map.cells[entity->y + y][entity->x + x].type == CELL_WALL)
		return ;
	entity->x += x;
	entity->y += y;
	app->nb_moves++;
	ft_printf("Moves: %d\n", app->nb_moves);
}

void	player_events(t_app *app)
{
	for (int i = 0; i < 100; i++)
	{
		if (app->collectibles[i] && app->player->x == app->collectibles[i]->x && app->player->y == app->collectibles[i]->y)
		{
			free(app->collectibles[i]);
			app->collectibles[i] = NULL;
			app->nb_collectibles--;
		}
	}
	if (app->player->x == app->exit->x && app->player->y == app->exit->y && app->nb_collectibles == 0)
		exit_program(app);
}

int	handle_key_press(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
		exit_program(app);
	else if (keycode == KEY_W)
		move_entity(app, app->player, 0, -1);
	else if (keycode == KEY_A)
		move_entity(app, app->player, -1, 0);
	else if (keycode == KEY_S)
		move_entity(app, app->player, 0, 1);
	else if (keycode == KEY_D)
		move_entity(app, app->player, 1, 0);
	player_events(app);
	draw_map(app);
	draw_entities(app);
	return (0);
}

int check_valid_chars(char **map)
{
	int i, j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C' &&
				map[i][j] != 'E' && map[i][j] != 'P')
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

void	free_map(char **map)
{
	int i;

	for (i = 0; map[i]; i++)
		free(map[i]);
	free(map);
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

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long path_to_file.ber\n");
		return (1);
	}
	init_app(&app);
	init_map(&app, argv[1]);
	check_map(&app, argv[1]);
	refresh_screen(&app);
	draw_map(&app);
	draw_entities(&app);
	mlx_hook(app.mlx_win, 17, 0, exit_program, &app);
	mlx_hook(app.mlx_win, 2, 1L << 0, handle_key_press, &app);
	mlx_loop(app.mlx);
	return (0);
}