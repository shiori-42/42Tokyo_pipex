/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:06:21 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/03 11:17:14 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;

	s_ptr = (unsigned char *)s;
	while (n--)
	{
		if (*s_ptr == (unsigned char)c)
			return (s_ptr);
		s_ptr++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*ch;

// 	char buf[] = "ABCD5EFGH";
// 	ch = (char *)ft_memchr(buf, '5', sizeof(buf));
// 	if (ch != NULL)
// 		printf("Result:%s\n", ch);
// 	else
// 		printf("Not Found");
// 	return (0);
// }
