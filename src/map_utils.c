/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:49:40 by tmarcos           #+#    #+#             */
/*   Updated: 2025/07/29 12:35:38 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void exit_with_error(char *msg)
{
    ft_printf("Error\n");
    ft_printf("%s\n", msg);     // Exibe o erro com cabeçalho padrão
    exit(EXIT_FAILURE);             // Finaliza o programa com código 1
}
void free_map(char **map)
{
	int i = 0;

	if (!map)
		return;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
