#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

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

// Init functions
void	init_map(t_app *app, char *filename);
void	init_app(t_app *app);
void	init_imgs(t_app *app);

// Draw functions
void	draw_map(t_app *app);
void	draw_entities(t_app *app);

// Event functions
void	player_events(t_app *app);
void	move_entity(t_app *app, t_entity *entity, int x, int y);
int		handle_key_press(int keycode, t_app *app);

// Check functions
int		check_valid_chars(char **map);
int		check_required_elements(char **map);
int		check_rectangle(char **map);
int		check_walls(char **map);
int		check_valid_path(char **map);
void	check_map(t_app *app, char *filename);

// Entity functions
void	add_collectible(t_app *app, int x, int y);
void	add_player(t_app *app, int x, int y);
void	add_exit(t_app *app, int x, int y);

// Free functions
void	free_map(char **map);
int		exit_program(t_app *app);

// Utils functions
char	*get_file_str(char *filename);
void	flood_fill(char **map, int x, int y);
int		ft_strslen(char **strs);
char	**copy_map_function(char **map);
void	refresh_screen(t_app *app);


#endif