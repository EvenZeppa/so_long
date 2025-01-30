#include "so_long.h"

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
