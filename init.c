/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:58:38 by ezeppa            #+#    #+#             */
/*   Updated: 2025/01/30 20:05:41 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_imgs(t_app *app)
{
	app->imgs.empty.img = mlx_xpm_file_to_image
		(app->mlx, "images/empty.xpm",
			&app->imgs.empty.width, &app->imgs.empty.height);
	app->imgs.player_a1.img = mlx_xpm_file_to_image
		(app->mlx, "images/player_a1.xpm",
			&app->imgs.player_a1.width, &app->imgs.player_a1.height);
	app->imgs.player_a2.img = mlx_xpm_file_to_image
		(app->mlx, "images/player_a2.xpm",
			&app->imgs.player_a2.width, &app->imgs.player_a2.height);
	app->imgs.wall.img = mlx_xpm_file_to_image
		(app->mlx, "images/wall.xpm",
			&app->imgs.wall.width, &app->imgs.wall.height);
	app->imgs.collectible.img = mlx_xpm_file_to_image
		(app->mlx, "images/collectible.xpm",
			&app->imgs.collectible.width, &app->imgs.collectible.height);
	app->imgs.exit.img = mlx_xpm_file_to_image
		(app->mlx, "images/exit.xpm",
			&app->imgs.exit.width, &app->imgs.exit.height);
}

void	set_map_dimensions(t_app *app, char **split)
{
	int	i;

	app->map.width = ft_strlen(split[0]);
	app->map.height = 0;
	i = 0;
	while (split[i])
	{
		app->map.height++;
		i++;
	}
}

void	init_cell(t_app *app, char **split, int i, int j)
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

void	init_map(t_app *app, char *filename)
{
	char	*map_str;
	char	**split;
	int		i;
	int		j;

	map_str = get_file_str(filename);
	if (!map_str)
	{
		ft_printf("Error\nUnable to open the file.\n");
		exit_program(app);
	}
	split = ft_split(map_str, '\n');
	set_map_dimensions(app, split);
	app->map.cells = malloc(app->map.height * sizeof(t_cell *));
	i = -1;
	while (++i < app->map.height)
	{
		app->map.cells[i] = malloc(app->map.width * sizeof(t_cell));
		j = -1;
		while (++j < app->map.width)
			init_cell(app, split, i, j);
		free(split[i]);
	}
	free(split);
	free(map_str);
}

void	init_app(t_app *app)
{
	int	i;

	app->mlx = mlx_init();
	app->mlx_win = mlx_new_window(app->mlx, 800, 800, "so_long");
	app->nb_moves = 0;
	app->nb_collectibles = 0;
	app->collectibles = malloc(sizeof(t_entity *) * 100);
	i = 0;
	while (i < 100)
	{
		app->collectibles[i] = NULL;
		i++;
	}
	app->player = malloc(sizeof(t_entity));
	app->exit = malloc(sizeof(t_entity));
	init_imgs(app);
}
