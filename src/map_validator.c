/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:49:30 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/06 18:40:17 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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

void	validate_characters(char **map, t_game *game)
{
	int	i;
	int	j;

	game->num_enemies = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' &&
				map[i][j] != 'P' && map[i][j] != 'C' &&
				map[i][j] != 'E' && map[i][j] != 'X')
				exit_with_error("Map contains invalid characters", game);
			if (map[i][j] == 'X')
				store_enemy(game, j, i);
			j++;
		}
		i++;
	}
}

int	count_chars(char **map, char c)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	validate_elements(char **map, t_game *game)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	player_count = count_chars(map, 'P');
	exit_count = count_chars(map, 'E');
	collectible_count = count_chars(map, 'C');
	if (player_count != 1)
		exit_with_error("Map must contain exactly one player", game);
	if (exit_count != 1)
		exit_with_error("Map must contain exactly one exit", game);
	if (collectible_count < 1)
		exit_with_error("Map must contain at least one collectible", game);
}

void	validate_walls(char **map, t_game *game)
{
	int	width;
	int	height;
	int	i;

	width = ft_strlen(map[0]);
	height = 0;
	while (map[height])
		height++;
	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			exit_with_error("Map is not enclosed by walls", game);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			exit_with_error("Map is not enclosed by walls", game);
		i++;
	}
}
