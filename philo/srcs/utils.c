/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:32:20 by qrolland          #+#    #+#             */
/*   Updated: 2023/03/24 15:40:33 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	exit(EXIT_FAILURE);
}

time_t	get_time_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *str, int i)
{
	pthread_mutex_lock(&(philo->data->message));
	if (dinner_is_ended(philo->data) && i == 0)
	{
		pthread_mutex_unlock(&(philo->data->message));
		return ;
	}
	printf("%ld %d %s\n", get_time_ms() - philo->data->start,
		philo->id_philo + 1, str);
	pthread_mutex_unlock(&(philo->data->message));
}

void	sychronize(time_t start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}

int	dinner_is_ended(t_data *data)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&data->lock_death);
	if (data->death == 1)
		end = 1;
	pthread_mutex_unlock(&data->lock_death);
	return (end);
}
