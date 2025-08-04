/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:55:45 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/01 17:55:46 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../custom_libs/libft/libft.h"
# include "../custom_libs/get_next_line/get_next_line.h"
# include "../lib/minilibx/mlx.h"

# define TILE_SIZE 64
# define MAX_ENEMIES 5

# ifdef __APPLE__
// macOS keycodes
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
# else
// Linux keycodes (ASCII-based)
#  define KEY_W 'w'
#  define KEY_A 'a'
#  define KEY_S 's'
#  define KEY_D 'd'
#  define KEY_ESC 65307
# endif

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_img
{
	void	*player;
	void	*wall;
	void	*floor;
	void	*collectible;
	void	*exit;
	void	*enemy;
	void	*move_counter;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	t_pos	player;
	int		collectibles;
	int		collected;
	int		moves;
	t_img	sprites;
	t_pos	enemies[MAX_ENEMIES];
	int		num_enemies;
}	t_game;

// maps
bool	has_ber_extension(char *filename);
void	exit_with_error(char *msg);
char	**read_map_file(char *file_path);
void	print_map(char **map); // debug
void	free_map(char **map);
void	validate_map(char **map, t_game *game);
void	validate_dimensions(char **map);
void	validate_characters(char **map, t_game *game);
void	validate_elements(char **map);
void	validate_walls(char **map);
char	**duplicate_map(char **map);
void	find_player(char **map, int *x, int *y);
void	flood_fill(char **map, int y, int x);
void	validate_path(char **map);
int		count_chars(char **map, char c);
// game
void	start_game(t_game *game, char *filepath);
void	init_game(t_game *game, char **map);
void	extract_map_data(t_game *game);
void	init_mlx(t_game *game);
void	load_tile(t_game *game, void **img, char *path);
void	load_sprites(t_game *game);
void	render_map(t_game *game);
int		handle_input(int keycode, t_game *game);
int		exit_hook(void *param);
void	exit_game(t_game *game);
void	draw_hud(t_game *game);
void	store_enemy(t_game *game, int x, int y);

#endif