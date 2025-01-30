/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:06:18 by ezeppa            #+#    #+#             */
/*   Updated: 2025/01/30 20:07:46 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_file_str(char *filename)
{
	int		fd;
	char	*file_str;
	char	*tmp_str;
	char	buf[2];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	file_str = malloc(1);
	file_str[0] = '\0';
	while (read(fd, buf, 1) > 0)
	{
		buf[1] = '\0';
		tmp_str = file_str;
		file_str = ft_strjoin(file_str, buf);
		free(tmp_str);
	}
	close(fd);
	return (file_str);
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

char	**copy_map_function(char **map)
{
	int		i;
	char	**copy_map;

	copy_map = malloc(sizeof(char *) * (ft_strslen(map) + 1));
	i = 0;
	while (map[i])
	{
		copy_map[i] = ft_strdup(map[i]);
		i++;
	}
	copy_map[i] = NULL;
	return (copy_map);
}
