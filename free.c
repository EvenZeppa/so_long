/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:55:05 by ezeppa            #+#    #+#             */
/*   Updated: 2025/01/30 19:57:58 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	destroy_images(t_app *app)
{
	mlx_destroy_image(app->mlx, app->imgs.empty.img);
	mlx_destroy_image(app->mlx, app->imgs.player_a1.img);
	mlx_destroy_image(app->mlx, app->imgs.player_a2.img);
	mlx_destroy_image(app->mlx, app->imgs.wall.img);
	mlx_destroy_image(app->mlx, app->imgs.collectible.img);
	mlx_destroy_image(app->mlx, app->imgs.exit.img);
}

int	exit_program(t_app *app)
{
	int	i;

	destroy_images(app);
	if (app->mlx_win)
		mlx_destroy_window(app->mlx, app->mlx_win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	i = -1;
	while (++i < app->map.height)
		free(app->map.cells[i]);
	free(app->map.cells);
	free(app->player);
	free(app->exit);
	i = -1;
	while (++i < 100)
		if (app->collectibles[i])
			free(app->collectibles[i]);
	free(app->collectibles);
	exit(0);
	return (0);
}

void	refresh_screen(t_app *app)
{
	mlx_destroy_window(app->mlx, app->mlx_win);
	app->mlx_win = mlx_new_window
		(app->mlx, app->map.width * 32, app->map.height * 32, "so_long");
}
