/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:13:46 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/01 17:45:04 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	int_to_str(int num, char *str)
{
	int		i;
	char	tmp[12];

	i = 0;
	if (num == 0)
		str[i++] = '0';
	while (num > 0)
	{
		tmp[i++] = (num % 10) + '0';
		num /= 10;
	}
	while (i--)
		*str++ = tmp[i];
	*str = '\0';
}

void	draw_hud(t_game *game)
{
	char	buffer[32];
	char	num[12];

	ft_memset(buffer, 0, sizeof(buffer));
	ft_memset(num, 0, sizeof(num));
	int_to_str(game->moves, num);
	ft_strlcpy(buffer, "Moves: ", sizeof(buffer));
	ft_strlcat(buffer, num, sizeof(buffer));
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, buffer);
}
