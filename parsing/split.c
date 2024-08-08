/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:35:51 by macampos          #+#    #+#             */
/*   Updated: 2024/08/08 10:42:31 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*word_aloc(char const *str, char c)
{
	char	*word;
	int		word_len;
	int		ctd;

	ctd = 0;
	word_len = 0;
	while (str[word_len] && str[word_len] != c)
		word_len++;
	word = (char *)malloc(word_len + 1);
	while (ctd < word_len)
	{
		word[ctd] = str[ctd];
		ctd++;
	}
	word[ctd] = '\0';
	return (word);
}

static int	count_words3(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		check;

	j = 0;
	i = 0;
	check = 1;
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

static int	count_words2(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		check;

	j = 0;
	i = 0;
	check = 1;
	if (!s)
        return (0);
	while (s[i])
	{
		if ((s[i] == '>' || s[i] == '<') && check == 1)
			return (j);
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

char	**ft_split2(char const *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = malloc((count_words2(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '>' || s[i] == '<')
			break ;
		if (s[i] != '\0' && s[i] != c)
		{
			ptr[j] = word_aloc(s + i, c);
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**ft_split3(char const *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = malloc((count_words3(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			ptr[j] = word_aloc3(s + i, c);
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}
