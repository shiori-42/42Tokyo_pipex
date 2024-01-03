/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:22:05 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/02 11:44:10 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// int main(void)
// {
//     char buffer[10]="Hello";
//     printf("Before bzero:");
//     for(size_t i=0;i<sizeof(buffer);++i)
//     {
//         printf("%u ",(unsigned char)buffer[i]);
//     }
//     printf("\n");

//     ft_bzero(buffer,sizeof(buffer));

//     printf("After bzero:");
//     for(size_t i=0;i<sizeof(buffer);++i)
//     {
//         printf("%u ",(unsigned char)buffer[i]);
//     }
//     printf("\n");
//     return(0);
// }