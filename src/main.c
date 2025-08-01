/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:36:05 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/01 12:38:16 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	char	**map;

	if (argc != 2)
		exit_with_error("Usage: ./so_long map.ber");
	if (!has_ber_extension(argv[1]))
		exit_with_error("Invalid file extension. Must be .ber");

	map = read_map_file(argv[1]);
	validate_map(map, &game);
	init_game(&game, map);
	init_mlx(&game);
	load_sprites(&game);
	render_map(&game);
	mlx_loop(game.mlx);
	free_map(game.map);
	return (0);
}
