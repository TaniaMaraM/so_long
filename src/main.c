/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:36:05 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/08 12:13:50 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	start_game(t_game *game, char *filepath)
{
	char	**map;

	ft_bzero(game, sizeof(t_game));
	map = read_map_file(filepath);
	game->map = map;
	validate_map(game->map, game);
	init_game(game, map);
	init_mlx(game);
	load_sprites(game);
	render_map(game);
	mlx_loop(game->mlx);
	free_map(game->map);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_with_error("Usage: ./so_long map.ber", NULL);
	if (!has_ber_extension(argv[1]))
		exit_with_error("Invalid file extension. Must be .ber", NULL);
	start_game(&game, argv[1]);
	return (0);
}
