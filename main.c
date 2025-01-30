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
}	t_app;

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

void	init_map(t_app *app, char *filename)
{
	char *map_str = "1111111111111\n10010000000C1\n1000011111001\n1P0011E000001\n1111111111111";
	char **split = ft_split(map_str, '\n');

	app->map.width = ft_strlen(split[0]);
	app->map.height = 5;
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
}

void	init_app(t_app *app)
{
	app->mlx = mlx_init();
	app->mlx_win = mlx_new_window(app->mlx, 800, 800, "so_long");
	
	app->nb_collectibles = 0;
	app->collectibles = malloc(sizeof(t_entity *) * 100);
	for (int i = 0; i < 100; i++)
		app->collectibles[i] = NULL;
	app->player = malloc(sizeof(t_entity));
	app->exit = malloc(sizeof(t_entity));
	
	init_map(app, "base.ber");
	mlx_destroy_window(app->mlx, app->mlx_win);
	app->mlx_win = mlx_new_window(app->mlx, app->map.width * 32, app->map.height * 32, "so_long");
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
	mlx_put_image_to_window(app->mlx, app->mlx_win, app->exit->a1->img, app->exit->x * 32, app->exit->y * 32);
	for (int i = 0; app->collectibles[i]; i++)
	{
		mlx_put_image_to_window(app->mlx, app->mlx_win, app->collectibles[i]->a1->img, app->collectibles[i]->x * 32, app->collectibles[i]->y * 32);
	}
	mlx_put_image_to_window(app->mlx, app->mlx_win, app->player->a1->img, app->player->x * 32, app->player->y * 32);
}

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

void	move_entity(t_app *app, t_entity *entity, int x, int y)
{
	if (app->map.cells[entity->y + y][entity->x + x].type == CELL_WALL)
		return ;
	entity->x += x;
	entity->y += y;
}

void	player_events(t_app *app)
{
	for (int i = 0; app->collectibles[i]; i++)
	{
		if (app->player->x == app->collectibles[i]->x && app->player->y == app->collectibles[i]->y)
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

int	main()
{
	t_app	app;

	init_app(&app);
	draw_map(&app);
	draw_entities(&app);
	mlx_hook(app.mlx_win, 17, 0, exit_program, &app);
	mlx_key_hook(app.mlx_win, handle_key_press, &app);
	mlx_loop(app.mlx);
	return (0);
}