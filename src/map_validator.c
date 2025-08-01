/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:49:30 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/01 12:41:37 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Percorre o mapa e conta quantos 'P', 'E' e 'C' existem
static void count_elements(char **map, int *p, int *e, int *c)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				(*p)++;
			else if (map[i][j] == 'E')
				(*e)++;
			else if (map[i][j] == 'C')
				(*c)++;
			j++;
		}
		i++;
	}
}

// Adiciona um inimigo à struct game se o limite não foi atingido
void	store_enemy(t_game *game, int x, int y)
{
	if (game->num_enemies < MAX_ENEMIES)
	{
		game->enemies[game->num_enemies].x = x;
		game->enemies[game->num_enemies].y = y;
		game->num_enemies++;
	}
	else
		exit_with_error("Too many enemies on map");
}
//garante que o mapa só contém caracteres válidos e armazena inimigos
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
				exit_with_error("Map contains invalid characters");
			if (map[i][j] == 'X')
				store_enemy(game, j, i);
			j++;
		}
		i++;
	}
}

// Valida se o mapa contém exatamente 1 P, 1 E, e pelo menos 1 C
void	validate_elements(char **map)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;
	
	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	count_elements(map, &player_count, &exit_count, &collectible_count);
	if (player_count != 1)
		exit_with_error("Map must contain exactly one player");
	if (exit_count != 1)
		exit_with_error("Map must contain exactly one exit");
	if (collectible_count < 1)
		exit_with_error("Map must contain at least one collectible");
}

// Garante que o mapa está completamente cercado por paredes
void	validate_walls(char **map)
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
			exit_with_error("Map is not enclosed by walls");
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			exit_with_error("Map is not enclosed by walls");
		i++;
	}
}
