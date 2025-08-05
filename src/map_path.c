/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:36:50 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/05 14:13:30 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	check_reachable(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
			{
				free_map(map);
				exit_with_error("Map has unreachable elements", NULL);
			}
			j++;
		}
		i++;
	}
}

void	validate_path(char **map)
{
	char	**copy;
	int		x;
	int		y;

	copy = duplicate_map(map);
	if (!copy)
		exit_with_error("Memory allocation failed", NULL);
	find_player(copy, &x, &y);
	flood_fill(copy, y, x);
	check_reachable(copy);
	free_map(copy);
}

/**
  duplicate_map - Creates a deep copy of the given map.
 
  @map: The original map to duplicate (null-terminated array of strings).
  
  Allocates a new char ** array and duplicates each line of the original map
  using ft_strdup, preserving the content without altering the original.
  This is especially useful for algorithms like flood fill, where the map
  must be modified during simulation but kept intact for rendering or logic.
 
  Returns:
 - A pointer to the duplicated map on success.
 - NULL on failure, with all allocated memory safely freed.
 */
//Permite rodar o flood fill sem modificar o mapa original

char	**duplicate_map(char **map)
{
	int		i;
	int		height;
	char	**copy;

	height = 0;
	while (map[height])
		height++;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

/**
 * find_player - Locate the starting position of the player ('P') in the map.
 *
 * @map: The game map to search (null-terminated array of strings).
 * @x: Pointer to store the player's column index.
 * @y: Pointer to store the player's row index.
 *
 * Searches the map for the character 'P' and stores its position in the
 * variables pointed by x and y. Exits with an error if not found.
 */
void	find_player(char **map, int *x, int *y)
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
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

/**
 * flood_fill - Recursively explores reachable tiles from a starting position.
 *
 * @map: The map to fill (this should be a duplicated map).
 * @y: Current row index.
 * @x: Current column index.
 *
	// Marks all accessible tiles from current position
	// using flood fill and replaces them with 'V'
	// to indicate visited.

 */
void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	if (map[y][x] == '0'
		|| map[y][x] == 'C'
		|| map[y][x] == 'E'
		|| map[y][x] == 'P')
		map[y][x] = 'V';
	else
		return ;
	flood_fill(map, y + 1, x); // down
	flood_fill(map, y - 1, x); // up
	flood_fill(map, y, x + 1); // right
	flood_fill(map, y, x - 1); // left
}
