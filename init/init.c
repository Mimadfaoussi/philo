/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:11:47 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/01 14:46:46 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	args_init(t_args *args, int argc, char **argv)
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

void	forks_init(pthread_mutex_t *forks, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	philo_init(t_philo *philos, t_args *args, t_data *data)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].is_eating = 0;
		philos[i].nb_meals = 0;
		philos[i].is_dead = &data->dead;
		philos[i].start_time = get_precise_time();
		philos[i].last_meal = get_precise_time();
		philos[i].left_fork = &data->forks[i];
		if (i == (args->nb_philos - 1))
			philos[i].right_fork = &data->forks[0];
		else
			philos[i].right_fork = &data->forks[i + 1];
		philos[i].eat_mutex = &data->eat_mutex;
		philos[i].dead_mutex = &data->dead_mutex;
		philos[i].print_mutex = &data->print_mutex;
		philos[i].args = args;
		i++;
	}
}

void	data_init(t_data *data, pthread_mutex_t *forks, t_philo *philos)
{
	data->dead = 0;
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->forks = forks;
	data->philos = philos;
}
