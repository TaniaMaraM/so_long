/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:50:27 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/01 16:47:57 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @file moves.c
 * @brief Handles player movement and input via keyboard.
 */

static bool	check_enemy_collision(t_game *game, int new_x, int new_y)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].x == new_x && game->enemies[i].y == new_y)
		{
			ft_printf("💀 You lost! Caught by an enemy!\n");
			exit_game(game);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	can_exit(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E' && game->collected < game->collectibles)
		return (false);
	return (true);
}

static bool	check_win(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E' && game->collected == game->collectibles)
	{
		ft_printf("🎉 You win in %d moves!\n", game->moves + 1);
		exit_game(game);
		return (true);
	}
	return (false);
}

static void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	next_tile;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	next_tile = game->map[new_y][new_x];
	if (next_tile == '1')
		return ;
	if (check_enemy_collision(game, new_x, new_y))
		return ;
	if (!can_exit(game, new_x, new_y))
		return ;
	if (next_tile == 'C')
		game->collected++;
	if (check_win(game, new_x, new_y))
		return ;
	game->map[game->player.y][game->player.x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player.x = new_x;
	game->player.y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
	draw_hud(game);
}

int	handle_input(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	else if (keycode == KEY_W)
		move_player(game, 0, -1);
	else if (keycode == KEY_S)
		move_player(game, 0, 1);
	else if (keycode == KEY_A)
		move_player(game, -1, 0);
	else if (keycode == KEY_D)
		move_player(game, 1, 0);
	return (0);
}

/* 
COM OS DEFINE EH PRA FUNCIONAR NO LINUX
pra funcionar no lINUX - testar na escola
int	handle_input(int keycode, t_game *game)
{
	ft_printf("KEY PRESSED: %d\n", keycode); //debug
	if (keycode == 65307 || keycode == 53) // ESC (Linux or Mac)
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
} */