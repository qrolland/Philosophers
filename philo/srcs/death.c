/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:25:10 by qrolland          #+#    #+#             */
/*   Updated: 2023/03/24 15:40:28 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	time_t	time;

	time = get_time_ms();
	if ((time - philo->started_eating) >= philo->data->args.time_to_die)
	{
		pthread_mutex_lock(&philo->data->lock_death);
		philo->data->death = 1;
		pthread_mutex_unlock(&philo->data->lock_death);
		print_status(philo, "died", 1);
		pthread_mutex_unlock(&philo->philo_mutex);
		return (1);
	}
	return (0);
}

static int	check_end(t_data *data)
{
	int	i;
	int	philos_ate;

	philos_ate = 1;
	i = 0;
	while (i < data->args.nb_of_philo)
	{
		pthread_mutex_lock(&data->philo[i]->philo_mutex);
		if (check_death(data->philo[i]))
			return (1);
		if (data->args.nb_of_meal != -1)
			if (data->philo[i]->count_meals
				< data->args.nb_of_meal)
				philos_ate = 0;
		pthread_mutex_unlock(&data->philo[i]->philo_mutex);
		i++;
	}
	if (data->args.nb_of_meal != -1 && philos_ate == 1)
	{
		pthread_mutex_lock(&data->lock_death);
		data->death = 1;
		pthread_mutex_unlock(&data->lock_death);
		return (1);
	}
	return (0);
}

void	*death_routine(void *args)
{
	t_data			*data;

	data = (t_data *)args;
	sychronize(data->start);
	while (1)
	{
		if (check_end(data) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
