/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:19:33 by qrolland          #+#    #+#             */
/*   Updated: 2023/03/24 15:27:28 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_args
{
	int		nb_of_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		nb_of_meal;
}				t_args;

typedef struct s_philo
{
	int				id_philo;
	int				count_meals;
	int				fork[2];
	time_t			started_eating;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	t_args			args;
	time_t			start;
	int				death;
	pthread_t		death_tracker;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	t_philo			**philo;
}			t_data;

long int	int_atol(char *str);
void		ft_error(char *str);
int			check_args(int argc, char **argv);
t_data		*init_data(int argc, char **argv);
time_t		get_time_ms(void);
void		*solo_routine(void *args);
void		sychronize(time_t start_time);
void		*philo_routine(void *args);
void		*death_routine(void *data);
void		stop_dinner(t_data	*data);
int			one_philo(t_data *data);
int			create_thread(t_data *data);
int			dinner_is_ended(t_data *data);
void		print_status(t_philo *philo, char *str, int i);

#endif