/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:51:56 by syonekur          #+#    #+#             */
/*   Updated: 2024/01/15 20:04:08 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			words++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (words);
}

char	*make_malloc_s_split(char *s, int word_length)
{
	int		i;
	char	*word;

	word = (char *)malloc(sizeof(char) * (word_length + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_length)
	{
		word[i] = s[i];
		i++;
	}
	word[word_length] = '\0';
	return (word);
}

void	*free_words(char **words_array, int i)
{
	while (i >= 0)
	{
		free(words_array[i]);
		i--;
	}
	free(words_array);
	return (NULL);
}

char	**set_word(char *s, char c, char **words_array, int s_words)
{
	int	word_length;
	int	j;
	int	i;

	j = 0;
	i = 0;
	word_length = 0;
	while (i < s_words)
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		word_length = 0;
		while (s[j] != c && s[j] != '\0')
		{
			word_length++;
			j++;
		}
		words_array[i] = make_malloc_s_split(&s[j - word_length], word_length);
		if (words_array[i] == NULL)
			free_words(words_array, i - 1);
		i++;
	}
	return (words_array);
}

char	**ft_split(char *s, char c)
{
	char	**words_array;
	int		s_words;

	if (s == NULL)
		return (NULL);
	s_words = count_words(s, c);
	words_array = (char **)malloc(sizeof(char *) * (s_words + 1));
	if (words_array == NULL)
		return (NULL);
	set_word(s, c, words_array, s_words);
	words_array[s_words] = NULL;
	return (words_array);
}

// int	main(void)
// {
// 	char	**tab;

// 	// char 	*s1;
// 	// char		set;
// 	// char		**splited;
// 	// s1 = "Hexllo Worlxd,Hxello evxeryoxne!";
// 	// set = 'x';
// 	tab = ft_split("  tripouille  42  ", ' ');
// 	// tab = ft_split(s1, set);
// 	// printf("%d\n", cnt_words(s1, set));
// 	for (int i = 0; tab[i]; i++)
// 	{
// 		printf("tab:%s\n", tab[i]);
// 		free(tab[i]);
// 	}
// 	free(tab);
// 	return (0);
// }
