/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:25:48 by syonekur          #+#    #+#             */
/*   Updated: 2023/10/10 22:57:27 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	check_overflow_num(const char *s, int sign)
{
	long	ans;
	long	max_div_ten;
	long	max_mod_ten;
	long	min_mod_ten;

	max_div_ten = LONG_MAX / 10;
	max_mod_ten = LONG_MAX % 10;
	min_mod_ten = max_mod_ten + 1;
	ans = 0;
	while (*s >= '0' && *s <= '9')
	{
		if (sign == 1 && (ans > max_div_ten || (ans == max_div_ten && (*s
						- '0') >= max_mod_ten)))
			return (LONG_MAX);
		if (sign == -1 && (ans > max_div_ten || (ans == max_div_ten && (*s
						- '0') >= min_mod_ten)))
			return (LONG_MIN);
		ans = ans * 10 + (*s - '0');
		s++;
	}
	return (ans * sign);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	ans;

	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	ans = check_overflow_num(str, sign);
	return ((int)ans);
}

// int	main(void)
// {
// 	char	*s;

// 	s = "-9223372036854775808";
// 	printf("org:%d\n", ft_atoi(s));
// 	printf("imi:%d\n", atoi(s));
// 	// printf("ans:%ld\n", LONG_MAX);
// 	// printf("ans:%ld\n", LONG_MIN);
// 	return (0);
// }
