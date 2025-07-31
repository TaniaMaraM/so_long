/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:27:08 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/31 20:40:53 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

//centraliza todas as validações obrigatórias do subject
void	validate_map(char **map, t_game *game)
{
	validate_dimensions(map);
	validate_characters(map, game);
	validate_elements(map);
	validate_walls(map);
}
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
bool	has_ber_extension(char *filename)
{
	int len;
	
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strcmp(filename + len - 4, ".ber") == 0)
		return (true);
	return (false);
}

// Lê o conteúdo do arquivo de mapa e retorna como um char ** (matriz de strings)
char **read_map_file(char *file_path)
{
	int		fd;
	char	*line;
	char	*full_map;
	char	*temp;
	char	**map;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_with_error("Could not open map file");
	full_map = NULL;
	while ((line = get_next_line(fd)))
	{
		temp = full_map;
		full_map = ft_strjoin(full_map, line);
		if (temp)
			free(temp);
		free(line);
	}
	close(fd);
	if (!full_map || full_map[0] == '\0')
		exit_with_error("Map is empty");

	map = ft_split(full_map, '\n');
	free(full_map);
	return (map);
}

