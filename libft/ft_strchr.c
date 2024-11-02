/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:54:16 by micongiu          #+#    #+#             */
/*   Updated: 2024/11/02 15:20:40 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned int	a;

	a = 0;
	while (str[a])
	{
		if (str[a] == (char)c)
			return ((char *)&str[a]);
		a++;
	}
	if (str[a] == (char) c)
		return ((char *)&str[a]);
	return (NULL);
}
