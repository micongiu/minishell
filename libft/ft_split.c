/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:53:54 by micongiu          #+#    #+#             */
/*   Updated: 2024/11/03 16:02:43 by anmedyns         ###   ########.fr       */
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
	size_t len = ft_strnlen(s, n);  // Determina la lunghezza fino a n caratteri
	char *new_str = malloc(len + 1);  // Alloca memoria per la nuova stringa

    if (new_str == NULL) {
        return NULL;  // Ritorna NULL se l'allocazione fallisce
    }

    if(ft_strlcpy(new_str, s, len))
		return(0);  // Copia fino a len caratteri
    new_str[len] = '\0';       // Assicura il terminatore nullo

    return new_str;
}


char	**ft_split(const char *str, char *delimiter)
{
    char **result = malloc(2 * sizeof(char *));
    if (!result)
        return NULL;

    // Trova la posizione del delimitatore
	char c = *delimiter;
    char *delim_pos = ft_strrchr(str, c);
    if (!delim_pos)
    {
        // Se il delimitatore non viene trovato, la stringa è solo un nome senza valore
        result[0] = ft_strdup_lib(str);
        result[1] = NULL;
    }
    else
    {
        // Copia la parte prima del delimitatore
        int name_len = delim_pos - str;
        result[0] = my_strndup(str, name_len);

        // Copia la parte dopo il delimitatore
        result[1] = ft_strdup_lib(delim_pos + 1);
    }
    return result;
}
