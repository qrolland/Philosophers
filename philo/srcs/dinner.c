/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:26:56 by qrolland          #+#    #+#             */
/*   Updated: 2023/03/24 15:25:48 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_data *data)
{
	data->start = get_time_ms();
	if (pthread_create(&(data->philo[0]->thread), NULL,
			&solo_routine, data->philo[0]))
		return (-1);
	pthread_join(data->philo[0]->thread, NULL);
	return (0);
}

int	create_thread(t_data *data)
{
	int	i;

	data->start = get_time_ms() + (data->args.nb_of_philo * 2 * 10);
	i = 0;
	while (i < data->args.nb_of_philo)
	{
		if (pthread_create(&data->philo[i]->thread, NULL,
				&philo_routine, data->philo[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&data->death_tracker, NULL,
			&death_routine, data) != 0)
		return (-1);
	return (0);
}

static void	*free_data(t_data *data)
{
	int	i;

	if (!data)
		return (NULL);
	if (data->forks != NULL)
		free(data->forks);
	if (data->philo != NULL)
	{
		i = 0;
		while (i < data->args.nb_of_philo)
		{
			if (data->philo[i] != NULL)
				free(data->philo[i]);
			i++;
		}
		free(data->philo);
	}
	free(data);
	return (NULL);
}

static void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nb_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i]->philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->message);
	pthread_mutex_destroy(&data->lock_death);
}

void	stop_dinner(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->args.nb_of_philo)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
	pthread_join(data->death_tracker, NULL);
	destroy_mutexes(data);
	free_data(data);
}
