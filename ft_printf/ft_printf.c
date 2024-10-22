/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:10:44 by micongiu          #+#    #+#             */
/*   Updated: 2024/02/08 23:32:38 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(const char str, va_list args, int i)
{
	if (str == 'd' || str == 'i')
		i += ft_putnbr_int(va_arg(args, int));
	else if (str == 's')
		i += ft_putstr(va_arg(args, char *));
	else if (str == 'c')
		i += ft_putchar(va_arg(args, int));
	else if (str == 'X')
		i += ft_put_hex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (str == 'x')
		i += ft_put_hex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (str == 'p')
		i += ft_put_pointer(va_arg(args, unsigned long), "0123456789abcdef");
	else if (str == 'u')
		i += ft_putnbr_unsint(va_arg(args, unsigned int));
	else if (str == '%')
		i += ft_putchar('%');
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		ret;
	int		a;

	ret = 0;
	a = 0;
	va_start(args, str);
	while (str[a])
	{
		if (str[a] == '%')
		{
			a++;
			ret = ft_check(str[a], args, ret);
		}
		else
			ret += ft_putchar(str[a]);
		a++;
	}
	va_end(args);
	return (ret);
}
