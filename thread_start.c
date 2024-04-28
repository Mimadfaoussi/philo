/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:41:28 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/04/28 16:54:05 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	not_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->is_dead) == 1)
	{
		pthread_mutex_unlock(philo->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->args->time_to_eat / 2);
	while (not_dead(philo) == 0)
	{
		// eat();
		// ft_sleep();
		// think();
		printf("my id is %d and i am not dead\n",philo->id);
		ft_usleep(200);
	}
	return (NULL);
}


void	threads_start(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	if (data->dead == 1)
		return ;
	while (i < philo->args->nb_philos)
	{
		if (pthread_create(&(philo[i].thread), NULL, &routine, &philo[i]) != 0)
		{
			printf("x_error\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < philo->args->nb_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("y_error\n");
			return ;
		}
		i++;
	}
}
