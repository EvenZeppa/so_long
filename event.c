/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:54:03 by ezeppa            #+#    #+#             */
/*   Updated: 2025/01/30 19:54:52 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	int	i;

	i = 0;
	while (i < 100)
	{
		if (app->collectibles[i] && app->player->x == app->collectibles[i]->x
			&& app->player->y == app->collectibles[i]->y)
		{
			free(app->collectibles[i]);
			app->collectibles[i] = NULL;
			app->nb_collectibles--;
		}
		i++;
	}
	if (app->player->x == app->exit->x && app->player->y == app->exit->y
		&& app->nb_collectibles == 0)
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
