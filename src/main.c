/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:36:05 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/29 19:28:19 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// int	main(int argc, char **argv)
// {
// 	t_game	game;

// 	if (argc != 2)
// 	{
// 		ft_printf("Error\nUsage: ./so_long map.ber\n");
// 		return (1);
// 	}
// 	ft_init_game(&game, argv[1]);      // lê mapa, valida, inicializa MLX
// 	ft_render_map(&game);              // renderiza mapa
// 	mlx_loop(game.mlx);                // entra no loop principal do jogo
// 	mlx_terminate(game.mlx);           // fecha tudo quando sair
// 	ft_free_map(game.map);             // libera memória do mapa
// 	return (0);
// }


#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**map;

	if (argc != 2)
		exit_with_error("Usage: ./so_long map.ber");
	if (!has_ber_extension(argv[1]))
		exit_with_error("Invalid file extension. Must be .ber");

	map = read_map_file(argv[1]);
	validate_map(map);       // Verifica dimensões, bordas, elementos
	validate_path(map);      // Garante que todos os 'C' e 'E' são acessíveis
	// print_map(map);       // ← Opcional: debug visual do mapa
	free_map(map);           // ← Sempre limpa a memória antes de sair
	return (0);
}