/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:11:47 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/04/28 14:15:52 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	args_init(t_data *args, int argc, char **argv)
{
	args->nb_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nb_meals = ft_atoi(argv[5]);
	else
		args->nb_meals = -1;
}

void	philo_init(t_philo *philos, t_args *args, t_data *data)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		philos[i].id = id;
		philos[i].is_eating = 0;
		philos[i].nb_meals = 0;
		philos[i].is_dead = 0;
		philos[i].start_time = get_precise_time();
		philos[i].last_meal = get_precise_time();
		philos[i].left_fork = &data->forks[i];
		if (i == (args->nb_philos - 1))
			philos[i].right_fork = &data->forks[0];
		else
			philos[i].right_fork = &data->forks[i + 1];
		philos[i].dead_mutex = &data->dead_mutex;
		philos[i].print_mutex = &data->print_mutex;
		philos[i].args = args;
		i++;
	}
}

