/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:49:30 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/29 18:08:15 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

//garante que o mapa é retangular
void	validate_dimensions(char **map)
{
	int i;
	int width;

	if (!map || !map[0])
		exit_with_error("Map is empty");
	width = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != width)
			exit_with_error("Map is not rectangular");
		i++;
	}
}
//garante que o mapa só contém caracteres válidos
void	validate_characters(char **map)
{
	int	i = 0;
	int	j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' &&
				map[i][j] != 'P' && map[i][j] != 'C' && map[i][j] != 'E')
				exit_with_error("Map contains invalid characters");
			j++;
		}
		i++;
	}
}

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

// Valida se o mapa contém exatamente 1 P, 1 E, e pelo menos 1 C
void	validate_elements(char **map)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;
	
	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	//Chama a função auxiliar para preencher os contadores.
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

	// Verifica primeira e última linha
	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			exit_with_error("Map is not enclosed by walls");
		i++;
	}
	// Verifica colunas laterais
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			exit_with_error("Map is not enclosed by walls");
		i++;
	}
}
