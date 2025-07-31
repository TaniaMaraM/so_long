/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:32:02 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/31 15:32:05 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @file mlx_setup.c
 * @brief Initializes the MLX context and opens a new game window.
 *
 * This file sets up the MiniLibX instance and the game window using the map dimensions.
 */

void	init_mlx(t_game *game)
{
	int	win_width;
	int	win_height;

	game->mlx = mlx_init();
	if (!game->mlx)
		exit_with_error("Failed to initialize MLX.");
	win_width = game->width * TILE_SIZE;
	win_height = game->height * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, win_width, win_height, "so_long");
	if (!game->win)
		exit_with_error("Failed to create game window.");
}
