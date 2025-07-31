/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:50:27 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/31 18:00:16 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @file moves.c
 * @brief Handles player movement and input via keyboard.
 */

static void	move_player(t_game *game, int dx, int dy)
{
	int	new_x = game->player.x + dx;
	int	new_y = game->player.y + dy;
	char	next_tile = game->map[new_y][new_x];

	if (next_tile == '1')
		return; // can't walk into walls
	if (next_tile == 'C')
		game->collected++;
	if (next_tile == 'E' && game->collected < game->collectibles)
		return; // can't exit yet

	game->map[game->player.y][game->player.x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player.x = new_x;
	game->player.y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
}

int	handle_input(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC
		exit_game(game);
	else if (keycode == 'w' || keycode == 119)
		move_player(game, 0, -1);
	else if (keycode == 's' || keycode == 115)
		move_player(game, 0, 1);
	else if (keycode == 'a' || keycode == 97)
		move_player(game, -1, 0);
	else if (keycode == 'd' || keycode == 100)
		move_player(game, 1, 0);
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_key_hook(game->win, handle_input, game);
	mlx_hook(game->win, 17, 0, exit_hook, game);
}

int	exit_hook(void *param)
{
	exit_game((t_game *)param);
	return (0);
}
