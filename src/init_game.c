/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:30:01 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/31 22:36:14 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @file init_game.c
 * @brief Initializes the main game structure and extracts essential data from the map.
 * 
 * This file contains functions responsible for:
 * - setting default values for the t_game structure
 * - extracting player position and map dimensions from the parsed map
 */

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
	if (x > game->width) //talvez de pra remover
	game->width = x;
}
/* 
Para cada linha do mapa:
    aumentar altura
    para cada caractere da linha:
        se for 'C' → incrementar collectibles
        se for 'P' → salvar posição do player
        se for 'X' → registrar inimigo com store_enemy
salvar largura como número de colunas da última linha
 */