/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:19:20 by syonekur          #+#    #+#             */
/*   Updated: 2023/09/27 20:00:35 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

// int	main(void)
// {
// 	for (int i = 0; i < UCHAR_MAX; ++i)
// 	{
// 		if (ft_isalnum(i))
// 		{
// 			printf("%c(%d)\n", i, i);
// 		}
// 	}
// }
