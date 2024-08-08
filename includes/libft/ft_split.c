/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:19:40 by macampos          #+#    #+#             */
/*   Updated: 2024/08/08 11:06:08 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char *word_aloc(char const *str, char c)
{
	char	*word;
	int		word_len;
	int		ctd;

	word_len = 0;
	ctd = 0;
	if (!str)
		return NULL;
	while (str[word_len] && str[word_len] != c)
		word_len++;
	word = (char *)malloc(word_len + 1);
	if (!word)
		return NULL;
	while (ctd < word_len)
	{
		word[ctd] = str[ctd];
		ctd++;
	}
	word[ctd] = '\0';
	return (word);
}

static int	count_words(char const *s, char c)
{
	size_t i;
	size_t j;
	int check;

	i = 0;
	j = 0;
	check = 1;
	if (!s)
		return 0;
	while (s[i])
	{
		if (s[i] != c && check == 1) 
		{
			j++;
			check = 0;
		}
		else if (s[i] == c)
			check = 1;
		i++;
	}
	return (j);
}


char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	if (!s)
		return NULL;
	ptr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return NULL;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			ptr[j] = word_aloc(s + i, c);
			if (!ptr[j])
			{
				while (j > 0)
					free(ptr[--j]);
				free(ptr);
				return NULL;
			}
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}