/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:36:05 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/05 14:16:06 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/*
 * Initializes and runs the game loop from the provided map file.
 * It loads and validates the map, sets up the game state and
 * starts the graphical window.
 */
void	start_game(t_game *game, char *filepath)
{
	char	**map;

	ft_bzero(game, sizeof(t_game));
	// Reads the .ber map file and stores it as a 2D char array.
	map = read_map_file(filepath);
	game->map = map;
	// Validates map rules (dimensions, characters, walls, paths...).
	//validate_map(map, game); //tentando achar os memory leaks
	validate_map(game->map, game);
	// Initializes game struct with player, collectibles, enemies, etc.
	init_game(game, map);
	// Initializes the MiniLibX graphics window and engine.
	init_mlx(game);
	// Loads all images (sprites) used in the game.
	load_sprites(game);
	// Renders the entire map on the window.
	render_map(game);
	// Starts the MLX event loop: listens for user input and keeps window open.
	mlx_loop(game->mlx);
	// Frees the memory allocated for the map at the end of the game.
	free_map(game->map);
}

/*
 * Entry point of the program.
 * Verifies arguments and delegates execution to start_game().
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_with_error("Usage: ./so_long map.ber", NULL);
	// Ensure the map file has the .ber extension.
	if (!has_ber_extension(argv[1]))
		exit_with_error("Invalid file extension. Must be .ber", NULL);
	// Run the full game logic using the provided map.
	start_game(&game, argv[1]);
	return (0);
}
/* 
int	main(int argc, char **argv)
{
	t_game	game;
	char	**map;

	if (argc != 2)
		exit_with_error("Usage: ./so_long map.ber", NULL);
	if (!has_ber_extension(argv[1]))
		exit_with_error("Invalid file extension. Must be .ber", NULL);
	map = read_map_file(argv[1]);
	validate_map(map, &game);
	init_game(&game, map);
	init_mlx(&game);
	load_sprites(&game);
	render_map(&game);
	mlx_loop(game.mlx);
	free_map(game.map);
	return (0);
} */