/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:09:23 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/02 19:25:35 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	aaaaa(unsigned int i, char *c)
// {
// 	(void)i;
// 	printf("%c", *c - ('a' - 'A'));
// 	return ;
// }

// int	main(void)
// {
// 	char	*s1;

// 	s1 = "abcdefghijklmn";
// 	ft_striteri(s1, &aaaaa);
// 	return (0);
// }
