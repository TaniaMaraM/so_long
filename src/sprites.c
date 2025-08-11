/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:49:16 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/06 22:09:45 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_tile(t_game *game, void **img, char *path)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!*img)
		exit_with_error("Failed to load sprite.", game);
}

void	load_sprites(t_game *game)
{
	load_tile(game, &game->sprites.floor, "assets/floor.xpm");
	load_tile(game, &game->sprites.wall, "assets/wall.xpm");
	load_tile(game, &game->sprites.player, "assets/player.xpm");
	load_tile(game, &game->sprites.collectible, "assets/collectible.xpm");
	load_tile(game, &game->sprites.exit, "assets/exit.xpm");
	load_tile(game, &game->sprites.enemy, "assets/enemy.xpm");
}
