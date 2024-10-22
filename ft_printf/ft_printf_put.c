/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:11:22 by micongiu          #+#    #+#             */
/*   Updated: 2024/02/08 23:33:24 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (write(1, "(null)", 6));
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr_unsint(unsigned int n)
{
	int	i;

	i = ft_count_num_unsi(n);
	if (n > 9)
	{
		ft_putnbr_unsint(n / 10);
		ft_putnbr_unsint(n % 10);
		i++;
	}
	else
		ft_putchar(n + '0');
	return (i);
}

int	ft_putnbr_int(int n)
{
	int	i;

	if (n == -2147483648)
	{
		i = ft_putstr("-2147483648");
		return (i);
	}
	i = ft_count_num(n);
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
		ft_putnbr_int(n);
	}
	else if (n > 9)
	{
		ft_putnbr_int(n / 10);
		ft_putnbr_int(n % 10);
		i++;
	}
	else
		ft_putchar(n + '0');
	return (i);
}
