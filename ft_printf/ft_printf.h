/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:11:12 by micongiu          #+#    #+#             */
/*   Updated: 2024/02/08 23:36:14 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_check(const char str, va_list args, int i);

int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr_unsint(unsigned int n);
int	ft_putnbr_int(int n);
int	ft_put_hex(unsigned int n, char *hex_char);
int	ft_put_pointer(unsigned long int n, char *hex_char);

int	ft_count_num(int n);
int	ft_count_num_unsi(unsigned int n);
int	ft_count_num_hex(unsigned int n);
int	ft_count_num_pointer(unsigned long int n);

#endif
