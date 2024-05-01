/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:41:28 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/04/28 19:37:50 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->args->time_to_eat / 2);
	while (not_dead(philo) == 0)
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}


int	thread_creation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->nb_philos)
	{
		if (pthread_create(&(philo[i].thread), NULL, &routine, &philo[i]) != 0)
		{
			printf("x_error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	thread_joining(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->nb_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("y_error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	threads_philos(t_philo *philo, t_data *data)
{
	pthread_t	checker;

	if (data->dead == 1)
		return ;
	if (pthread_create(&checker, NULL, &checker_routine, philo) != 0)
	{
		printf("x_error\n");
		return ;
	}
	thread_creation(philo);
	thread_joining(philo);
	if (pthread_join(checker, NULL) != 0)
	{
		printf("y_error\n");
		return ;
	}
	// printf("finished successfully \n");
}

