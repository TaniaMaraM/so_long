/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:49:40 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/01 12:40:59 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void exit_with_error(char *msg)
{
    ft_printf("Error\n");
    ft_printf("%s\n", msg);
    exit(EXIT_FAILURE);
}
void free_map(char **map)
{
	int	i;
	
	i = 0;
	if (!map)
		return;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
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
