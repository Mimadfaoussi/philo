/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:40:56 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/02 10:38:06 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	printall(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->args->nb_philos)
// 	{
// 		printf("philo id : %d\n",philo[i].id);
// 		printf("philo is_eating : %d\n",philo[i].is_eating);
// 		printf("philo nb_meals : %d\n",philo[i].nb_meals);
// 		printf("philo left_fork : %p\n",philo[i].left_fork);
// 		printf("philo right_fork : %p\n",philo[i].right_fork);
// 		printf("philo start_time : %llu\n",philo[i].start_time);
// 		printf("---------------------------\n");
// 		i++;
// 	}
// }

int	main(int argc, char **argv)
{
	pthread_mutex_t	forks[MAX_PHILOS];
	t_philo			philos[MAX_PHILOS];
	t_args			args;
	t_data			data;

	if (check_input(argc, argv) == 1)
	{
		printf("input error\n");
		return (1);
	}
	args_init(&args, argc, argv);
	if (forks_init(forks, &args) == 1)
		return (1);
	if (data_init(&data, forks, philos) == 1)
		return (1);
	philo_init(philos, &args, &data);
	threads_philos(philos, &data);
	destroy_all(forks, &data);
	return (0);
}
