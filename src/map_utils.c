/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:49:40 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/04 16:25:58 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	exit_with_error(char *msg, t_game *game)
{
	ft_printf("Error\n");
	ft_printf("%s\n", msg);
	if (game)
	{
		free_map(game->map);
		exit_game(game);
	}
	exit(EXIT_FAILURE);
}

/**
 * count_chars - Counts how many times a specific character appears in the map.
 * @map: 2D map array (char **)
 * @c: Character to count
 * 
 * Returns the number of times the character `c` appears in the map.
 */
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

