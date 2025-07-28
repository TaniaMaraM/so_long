/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcos <tmarcos@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:34:38 by tmarcos           #+#    #+#             */
/*   Updated: 2024/12/04 17:09:57 by tmarcos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str_dest;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str_dest = (char *)malloc(len1 + len2 + 1);
	if (str_dest == NULL)
		return (NULL);
	ft_strlcpy(str_dest, s1, len1 + 1);
	ft_strlcpy(str_dest + len1, s2, len2 + 1);
	return (str_dest);
}
