/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:36:50 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/29 19:19:21 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


/**
 * validate_path - Ensures all collectibles and exit are reachable from player.
 *
 * @map: The original, validated game map.
 *
 * This function duplicates the map, finds the player's position, runs
 * flood fill, and then checks if any 'C' or 'E' remain unvisited.
 * If any target is unreachable, it exits the program with an error.
 */
void	validate_path(char **map)
{
	char	**copy;
	int		x, y;
	int		i, j;

	copy = duplicate_map(map);
	if (!copy)
		exit_with_error("Memory allocation failed during path validation");
	find_player(copy, &x, &y);
	flood_fill(copy, y, x);
	i = 0;
	while (copy[i])
	{
		j = 0;
		while (copy[i][j])
		{
			if (copy[i][j] == 'C' || copy[i][j] == 'E')
			{
				free_map(copy);
				exit_with_error("Map has unreachable elements");
			}
			j++;
		}
		i++;
	}
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

	// Conta quantas linhas tem o mapa
	height = 0;
	while (map[height])
		height++;
	// Aloca espaço para o novo mapa (mais um para o NULL final)
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		//Se der erro, libera todas as linhas que já tinham sido duplicadas.
        if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL); //indica que deu erro
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
				return;
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
 * Marks all accessible tiles ('0', 'C', 'E') from the given position by
 * replacing them with 'V' to indicate visited.
 */
void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == '1' || map[y][x] == 'V')
		return;
	if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'E' || map[y][x] == 'P')
		map[y][x] = 'V';
	else
		return;
	flood_fill(map, y + 1, x); // down
	flood_fill(map, y - 1, x); // up
	flood_fill(map, y, x + 1); // right
	flood_fill(map, y, x - 1); // left
}
