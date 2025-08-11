/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:27:08 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/06 17:09:05 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	validate_map(char **map, t_game *game)
{
	validate_dimensions(map, game);
	validate_characters(map, game);
	validate_elements(map, game);
	validate_walls(map, game);
	validate_path(map);
}

void	validate_dimensions(char **map, t_game *game)
{
	int	i;
	int	width;

	if (!map || !map[0])
		exit_with_error("Map is empty", game);
	width = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != width)
			exit_with_error("Map is not rectangular", game);
		i++;
	}
}

bool	has_ber_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strcmp(filename + len - 4, ".ber") == 0)
		return (true);
	return (false);
}

static char	*read_full_map(int fd)
{
	char	*line;
	char	*full_map;
	char	*temp;

	full_map = NULL;
	line = get_next_line(fd);
	while (line)
	{
		temp = full_map;
		full_map = ft_strjoin(full_map, line);
		if (temp)
			free(temp);
		free(line);
		line = get_next_line(fd);
	}
	return (full_map);
}

char	**read_map_file(char *file_path)
{
	int		fd;
	char	*full_map;
	char	**map;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_with_error("Could not open map file", NULL);
	full_map = read_full_map(fd);
	close(fd);
	if (!full_map || full_map[0] == '\0')
		exit_with_error("Map is empty", NULL);
	map = ft_split(full_map, '\n');
	free(full_map);
	return (map);
}
