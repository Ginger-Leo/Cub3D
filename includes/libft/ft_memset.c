/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:06:39 by mmeier            #+#    #+#             */
/*   Updated: 2023/11/03 15:33:33 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*p;

	p = b;
	while (len != 0)
	{
		*p++ = (unsigned char)(c);
		len--;
	}
	return (b);
}
