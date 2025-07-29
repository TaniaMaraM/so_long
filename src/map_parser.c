/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:27:08 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/29 12:25:57 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		ft_printf("DEBUG: linha lida: %s", line);
		ft_printf("DEBUG: full_map parcial: %s\n", full_map);
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

// DEBUG Função para imprimir o mapa no terminal
void print_map(char **map)
{
	int i = 0;

	if (!map)
		ft_printf("DEBUG: map is NULL\n");

	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}
