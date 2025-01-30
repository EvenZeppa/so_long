#include "so_long.h"

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
