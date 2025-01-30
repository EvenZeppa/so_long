/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:53:38 by ezeppa            #+#    #+#             */
/*   Updated: 2025/01/30 19:53:40 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
