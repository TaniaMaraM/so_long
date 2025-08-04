/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:17:26 by tmarcos           #+#    #+#             */
/*   Updated: 2025/08/01 17:53:28 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

int		ft_find_newline(const char *str);
char	*ft_extract_line(char *keep);
char	*ft_update_keep(char *keep);
char	*ft_read_file(int fd, char *keep);
char	*get_next_line(int fd);

#endif