/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:34:30 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/03 11:17:44 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_ptr[i] != s2_ptr[i])
			return ((unsigned char)s1_ptr[i] - (unsigned char)s2_ptr[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char buf[] = "ABCD5EFGH";
// 	char buf2[] = "ABC123456";

// 	if (ft_memcmp(buf, buf2, 3) == 0)
// 		printf("Match 3bytes");
// 	else
// 		printf("NO Match");
// 	return (0);
// }