/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:25:24 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/10 20:50:30 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

// int	main(void)
// {
// 	char *s1 = NULL;

// 	printf("%s(%zu)\n", s1, strlen(s1));
// 	printf("%s(%zu)\n", s1, ft_strlen(s1));
// 	return (0);
// }