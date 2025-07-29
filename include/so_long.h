/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:46:57 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/29 13:55:22 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> //para teste
# include "../custom_libs/libft/libft.h"
# include "../custom_libs/get_next_line/get_next_line.h"


#include <MLX42/MLX42.h>

# define TILE_SIZE 64

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos; //Guarda uma posição x e y, útil pra player, collectibles, etc.

typedef struct s_img
{
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
}	t_img; //Guarda todos os sprites carregados.

typedef struct s_game
{
	mlx_t		*mlx; // contexto da MLX
	// mlx_image_t	**map_imgs;  // opcional: para gerenciar imagens
	char		**map; // matriz de chars com os dados do mapa
	int			width; // largura do mapa
	int			height; // altura do mapa
	// t_pos		player; // posição atual do player
	// int			collectibles; // total de "C" no mapa
	// int			collected; // quantos já pegou
	// int			moves; // número de movimentos
	// t_img		sprites; // imagens carregadas
}	t_game; //estrutura do jogo

// Function Prototypes
void	ft_init_game(t_game *game, char *file);
void	ft_error_exit(char *msg, t_game *game);
void	ft_render_map(t_game *game);
void	ft_move_player(t_game *game, int dx, int dy);
int		ft_valid_map(char **map);
void	ft_free_map(char **map);


bool	has_ber_extension(char *filename);
void	exit_with_error(char *msg);
char	**read_map_file(char *file_path);
void	print_map(char **map); //para debug


#endif