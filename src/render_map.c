/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:49:14 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/01 17:09:43 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @file render_map.c
 * @brief Renders the full game map onto the window using MiniLibX.
 *
 * Iterates over the map matrix and places the correct tiles and sprites
 * at each position based on the character found.
 */
//Sempre desenha o floor como camada base
//(assim como no Paint: primeiro fundo, depois objetos por cima)
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
