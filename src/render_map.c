/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:49:14 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/06 22:10:11 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	render_tile(t_game *game, char tile, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->sprites.floor, x * TILE_SIZE, y * TILE_SIZE);
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.collectible, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.exit, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'X')
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.enemy, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'P')
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.player, x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_enemies(t_game *game)
{
	int	i;
	int	ex;
	int	ey;

	i = 0;
	while (i < game->num_enemies)
	{
		ex = game->enemies[i].x * TILE_SIZE;
		ey = game->enemies[i].y * TILE_SIZE;
		mlx_put_image_to_window(game->mlx, game->win,
			game->sprites.enemy, ex, ey);
		i++;
	}
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			render_tile(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
	render_enemies(game);
}
