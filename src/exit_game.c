/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:53:38 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/04 21:24:41 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @file exit_game.c
 * @brief Handles clean exit of the game when ESC 
 * is pressed or window is closed.
 */

void	exit_game(t_game *game)
{
	if (game->sprites.player)
		mlx_destroy_image(game->mlx, game->sprites.player);
	if (game->sprites.wall)
		mlx_destroy_image(game->mlx, game->sprites.wall);
	if (game->sprites.floor)
		mlx_destroy_image(game->mlx, game->sprites.floor);
	if (game->sprites.collectible)
		mlx_destroy_image(game->mlx, game->sprites.collectible);
	if (game->sprites.exit)
		mlx_destroy_image(game->mlx, game->sprites.exit);
	if (game->sprites.enemy)
		mlx_destroy_image(game->mlx, game->sprites.enemy);
	if (game->sprites.move_counter) //testing leaks
		mlx_destroy_image(game->mlx, game->sprites.move_counter); //testing leaks
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		//mlx_destroy_display(game->mlx); //testing leaks
		free(game->mlx);
	}
	if (game->map)
		free_map(game->map);
	ft_printf("Game closed. Total moves: %d\n", game->moves);
	exit(0);
}

int	exit_hook(void *param)
{
	exit_game((t_game *)param);
	return (0);
}
