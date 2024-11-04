/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:53:54 by micongiu          #+#    #+#             */
/*   Updated: 2024/11/03 18:21:39 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	is_separator(char ch, const char *sep)
{
	int i;
	i = 0;
	while (sep[i])
	{
		if (ch == sep[i])
			return (1);
		i++;
	}
	return (0);
}
int count_words(const char *s, const char *separators)
{
	int count = 0;
	int in_word = 0;

	while (*s)
	{
		if (!is_separator(*s, separators) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_separator(*s, separators))
		{
			in_word = 0;
		}
		s++;
	}
	return count;
}

int ft_strnlen(const char *str, char n)
{
	size_t	a;
	char p = n;
	a = 0;
	while (str[a] != p)
		a++;
	return (a);
}

char *my_strndup(const char *s, size_t n)
{
	size_t len = ft_strnlen(s, n);
	char *new_str = malloc(len + 1);

	if (new_str == NULL)
		return NULL;
	if(ft_strlcpy(new_str, s, len))
		return(0);
	new_str[len] = '\0';
	return new_str;
}

char	**ft_split(const char *str, char *delimiter)
{
	char **result = malloc(2 * sizeof(char *));
	if (!result)
		return NULL;
	char c = *delimiter;
	char *delim_pos = ft_strrchr(str, c);
	if (!delim_pos)
	{
		result[0] = ft_strdup_lib(str);
		result[1] = NULL;
	}
	else
	{
		int name_len = delim_pos - str;
		result[0] = my_strndup(str, name_len);
		result[1] = ft_strdup_lib(delim_pos + 1);
	}
	return result;
}
