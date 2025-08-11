/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:30:01 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/11 22:01:01 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_game(t_game *game, char **map)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = map;
	game->height = 0;
	game->width = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->moves = 0;
	game->num_enemies = 0;
	game->sprites.player = NULL;
	game->sprites.wall = NULL;
	game->sprites.floor = NULL;
	game->sprites.collectible = NULL;
	game->sprites.exit = NULL;
	game->sprites.enemy = NULL;
	game->sprites.move_counter = NULL;
	extract_map_data(game);
}

void	extract_map_data(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		game->height++;
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
				game->collectibles++;
			else if (game->map[y][x] == 'P')
			{
				game->player.x = x;
				game->player.y = y;
			}
			else if (game->map[y][x] == 'X')
				store_enemy(game, x, y);
			x++;
		}
		y++;
	}
	if (x > game->width)
		game->width = x;
}

void	store_enemy(t_game *game, int x, int y)
{
	if (game->num_enemies < MAX_ENEMIES)
	{
		game->enemies[game->num_enemies].x = x;
		game->enemies[game->num_enemies].y = y;
		game->num_enemies++;
	}
	else
		exit_with_error("Too many enemies on map", game);
}
