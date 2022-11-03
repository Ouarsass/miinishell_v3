/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:20:15 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/02 21:52:03 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*r;
	size_t	j;

	j = 0;
	if (!(r = (char *)malloc(size + 1 * sizeof(*r))))
		return (NULL);
	while (j <= size)
		r[j++] = '\0';
	return (r);
}
