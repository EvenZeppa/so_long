#include "so_long.h"

void	free_map(char **map)
{
	int i;

	for (i = 0; map[i]; i++)
		free(map[i]);
	free(map);
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

void	refresh_screen(t_app *app)
{
	mlx_destroy_window(app->mlx, app->mlx_win);
	app->mlx_win = mlx_new_window(app->mlx, app->map.width * 32, app->map.height * 32, "so_long");
}
