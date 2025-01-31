/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:49:47 by ezeppa            #+#    #+#             */
/*   Updated: 2025/01/30 19:53:07 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_app *app)
{
	int	i;
	int	j;

	i = 0;
	while (i < app->map.height)
	{
		j = 0;
		while (j < app->map.width)
		{
			if (app->map.cells[i][j].type == CELL_WALL)
				mlx_put_image_to_window(app->mlx,
					app->mlx_win, app->imgs.wall.img, j * 32, i * 32);
			else
			{
				mlx_put_image_to_window(app->mlx,
					app->mlx_win, app->imgs.empty.img, j * 32, i * 32);
			}
			j++;
		}
		i++;
	}
}

void	draw_entities(t_app *app)
{
	static int	time_anim = 0;
	int			i;

	mlx_put_image_to_window(app->mlx,
		app->mlx_win, app->exit->a1->img, app->exit->x * 32, app->exit->y * 32);
	i = 0;
	while (i < 100)
	{
		if (app->collectibles[i])
			mlx_put_image_to_window(app->mlx, app->mlx_win,
				app->collectibles[i]->a1->img,
				app->collectibles[i]->x * 32, app->collectibles[i]->y * 32);
		i++;
	}
	if (time_anim % 10 < 5)
		mlx_put_image_to_window(app->mlx, app->mlx_win,
			app->player->a2->img, app->player->x * 32, app->player->y * 32);
	else
		mlx_put_image_to_window(app->mlx, app->mlx_win,
			app->player->a1->img, app->player->x * 32, app->player->y * 32);
	time_anim++;
}
