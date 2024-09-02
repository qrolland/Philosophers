/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:17:03 by qrolland          #+#    #+#             */
/*   Updated: 2023/03/24 14:22:09 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_to_sleep(t_data *data, time_t sleep)
{
	time_t	wake;

	wake = get_time_ms() + sleep;
	while (get_time_ms() < wake && !dinner_is_ended(data))
		usleep(100);
}

void	*solo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->data->forks[philo->fork[0]]);
	print_status(philo, "has taken a fork", 0);
	time_to_sleep(philo->data, philo->data->args.time_to_die);
	print_status(philo, "died", 1);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[0]]);
	return (NULL);
}

static void	time_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork[0]]);
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->data->forks[philo->fork[1]]);
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->philo_mutex);
	print_status(philo, "is eating", 0);
	philo->started_eating = get_time_ms();
	pthread_mutex_unlock(&(philo->philo_mutex));
	time_to_sleep(philo->data, philo->data->args.time_to_eat);
	if (!dinner_is_ended(philo->data))
	{
		pthread_mutex_lock(&philo->philo_mutex);
		philo->count_meals++;
		pthread_mutex_unlock(&(philo->philo_mutex));
	}
	pthread_mutex_unlock(&philo->data->forks[philo->fork[0]]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[1]]);
}

time_t	think_time(t_philo *philo, int i)
{
	time_t	time;

	pthread_mutex_lock(&philo->philo_mutex);
	time = (philo->data->args.time_to_die
			- (get_time_ms() - philo->started_eating)
			- philo->data->args.time_to_eat) / 2;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (time < 0)
		time = 0;
	if (time == 0 && i == 0)
		time = 1;
	if (time > 500)
		time = 200;
	return (time);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->data->args.time_to_die == 0)
		return (NULL);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->started_eating = philo->data->start;
	pthread_mutex_unlock(&philo->philo_mutex);
	sychronize(philo->data->start);
	if (philo->id_philo % 2)
		time_to_sleep(philo->data, think_time(philo, 0));
	while (!dinner_is_ended(philo->data))
	{
		time_to_eat(philo);
		print_status(philo, "is sleeping", 0);
		time_to_sleep(philo->data, philo->data->args.time_to_sleep);
		print_status(philo, "is thinking", 0);
		time_to_sleep(philo->data, think_time(philo, 1));
	}
	return (NULL);
}
