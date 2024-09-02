/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:22:45 by qrolland          #+#    #+#             */
/*   Updated: 2023/03/24 14:24:56 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	str_isint(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

long int	int_atol(char *str)
{
	long int	nb;

	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		str++;
	}
	return (nb);
}

int	check_args(int argc, char **argv)
{
	int			i;
	long int	nb;

	i = 1;
	while (i < argc)
	{
		nb = int_atol(argv[i]);
		if (!str_isint(argv[i]) || (i == 1 && (nb == 0 || nb > 200))
			|| (i == 5 && nb == 0) || nb > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}
