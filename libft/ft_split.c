/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:53:54 by micongiu          #+#    #+#             */
/*   Updated: 2024/11/01 16:23:04 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	is_separator(char ch, const char *sep)
{
	int i = 0;
	while (sep[i]) {
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


// static void	free_matrix(char **matrix)
// {
// 	size_t	i;

// 	i = 0;
// 	if (matrix == NULL)
// 		return ;
// 	while (matrix[i])
// 	{
// 		free(matrix[i]);
// 		i++;
// 	}
// 	free(matrix);
// 	matrix = NULL;
// }



char	**ft_split(const char *s, char *separators)
{
	size_t	k;
	size_t	j;
	int		pos;
	char	**matrix;

	if (!s || !separators)
		return (NULL);
	matrix = ft_calloc((count_words(s, separators) + 1), sizeof(char *));
	if (!matrix)
		return (NULL);
	k = -1;
	j = 0;
	pos = -1;
	while (++k <= ft_strlen_lib(s))
	{
		if (!is_separator(s[k], separators) && pos < 0)
			pos = k;
		if ((is_separator(s[k], separators) || k == ft_strlen_lib(s)) && pos >= 0)
		{
			matrix[j++] = ft_substr_lib(s, pos, (k - pos));
			pos = -1;
		}
	}
	matrix[j] = NULL;
	return (matrix);
}
