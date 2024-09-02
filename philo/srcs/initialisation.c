/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:11 by qrolland          #+#    #+#             */
/*   Updated: 2023/03/24 14:37:29 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	**init_philo(t_data *data)
{
	t_philo	**philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data->args.nb_of_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->args.nb_of_philo)
	{
		philo[i] = malloc(sizeof(t_philo) * 1);
		if (!philo[i])
			return (NULL);
		philo[i]->data = data;
		philo[i]->id_philo = i;
		philo[i]->count_meals = 0;
		philo[i]->fork[0] = (i + i % 2) % data->args.nb_of_philo;
		philo[i]->fork[1] = (i + 1 - i % 2) % data->args.nb_of_philo;
		if (pthread_mutex_init(&philo[i]->philo_mutex, 0))
			return (NULL);
		i++;
	}
	return (philo);
}

static pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->args.nb_of_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->args.nb_of_philo)
	{
		if (pthread_mutex_init(&forks[i], 0))
			return (NULL);
		i++;
	}
	return (forks);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	data->args.nb_of_philo = int_atol(argv[1]);
	data->args.time_to_die = int_atol(argv[2]);
	data->args.time_to_eat = int_atol(argv[3]);
	data->args.time_to_sleep = int_atol(argv[4]);
	if (argc == 6)
		data->args.nb_of_meal = int_atol(argv[5]);
	else
		data->args.nb_of_meal = -1;
	data->death = 0;
	data->philo = init_philo(data);
	if (!data->philo)
		return (NULL);
	data->forks = init_forks(data);
	if (!data->forks)
		return (NULL);
	if (pthread_mutex_init(&data->message, 0))
		return (NULL);
	if (pthread_mutex_init(&data->lock_death, 0))
		return (NULL);
	return (data);
}
