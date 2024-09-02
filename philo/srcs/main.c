/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:31:58 by qrolland          #+#    #+#             */
/*   Updated: 2023/03/24 14:31:59 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc < 5 || argc > 6)
		ft_error("Wrong number of arguments\n");
	if (!check_args(argc, argv))
		ft_error("Invalid arguments\n");
	data = init_data(argc, argv);
	if (!data)
		return (-1);
	if (data->args.nb_of_philo == 1)
		one_philo(data);
	else
		create_thread(data);
	stop_dinner(data);
	return (0);
}
