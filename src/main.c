/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:36:05 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/28 14:36:07 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long map.ber\n");
		return (1);
	}
	ft_init_game(&game, argv[1]);      // lê mapa, valida, inicializa MLX
	ft_render_map(&game);              // renderiza mapa
	mlx_loop(game.mlx);                // entra no loop principal do jogo
	mlx_terminate(game.mlx);           // fecha tudo quando sair
	ft_free_map(game.map);             // libera memória do mapa
	return (0);
}