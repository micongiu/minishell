/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_puthex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:59:05 by micongiu          #+#    #+#             */
/*   Updated: 2024/02/08 23:42:43 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_hex(unsigned int n, char *hex_char)
{
	int		i;
	char	*res;

	i = ft_count_num_hex(n);
	res = (char *)malloc(i + 1);
	if (!res)
		return (0);
	res[i--] = '\0';
	if (n == 0)
	{
		ft_putchar('0');
		free(res);
		return (1);
	}
	while (n != 0)
	{
		res[i] = hex_char[n % 16];
		n = n / 16;
		i--;
	}
	i = -1;
	while (res[++i] != '\0')
		ft_putchar(res[i]);
	free(res);
	return (i);
}

int	ft_put_pointer(unsigned long int n, char *hex_char)
{
	int		i;
	char	*res;

	i = ft_count_num_pointer(n);
	if (n == 0)
		return (ft_putstr("0x0"));
	res = (char *)malloc(i + 1);
	if (!res)
		return (0);
	res[i--] = '\0';
	while (n != 0)
	{
		res[i] = hex_char[n % 16];
		n = n / 16;
		i--;
	}
	i = -1;
	ft_putstr("0x");
	while (res[++i] != '\0')
		ft_putchar(res[i]);
	free(res);
	return (i + 2);
}
