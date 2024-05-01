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
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

int	philo_is_dead(t_philo *philo)
{
	u_int64_t	time;

	time = get_precise_time() - philo->last_meal;
	if (time >= philo->args->time_to_die)
	{
		return (1);
	}
	return (0);
}

int	check_all(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->args->nb_philos)
	{
		if (philo_is_dead(&philo[i]) == 1)
		{
			pthread_mutex_lock(philo->dead_mutex);
			print_mutex(&philo[i], "is dead");
			*(philo->is_dead) = 1;
			pthread_mutex_unlock(philo->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*checker_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_all(philo) == 0)
	{
		continue ;
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
	if (data->dead == 1)
		return ;
	thread_creation(philo);
	thread_joining(philo);
}

// void	threads_checker(t_philo *philo, t_data *data)
// {
// 	pthread_t	checker;

// 	if (pthread_create(&checker, NULL, &checker_routine, data) != 0)
// 	{
// 		printf("error checker\n");
// 		return ;
// 	}
// 	if (pthread_join(checker, NULL) != 0)
// 	{
// 		printf("error checker\n");
// 		return ;
// 	}

// }
