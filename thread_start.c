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

// int	philo_is_dead(t_philo *philo)
// {
// 	u_int64_t	time;

// 	time = get_precise_time() - philo->last_meal;
// 	if (time >= philo->args->time_to_die)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	*(philo->is_dead) = 1;
	pthread_mutex_unlock(philo->dead_mutex);
}

void	check_all_died(t_philo *philo)
{
	int		i;
	u_int64_t	time;

	i = 0;
	while (i < philo->args->nb_philos)
	{
		pthread_mutex_lock(philo->eat_mutex);
		time = get_precise_time() - philo[i].last_meal;
		pthread_mutex_unlock(philo->eat_mutex);
		if (time >= philo->args->time_to_die)
		{
			print_mutex(&philo[i], "died");
			set_dead(philo);
			return ;
		}
		i++;
	}
	return ;
}
void	check_all_ate(t_philo *philo)
{
	int	i;
	int	all_ate;

	if (philo->args->nb_meals == -1)
		return ;
	all_ate = 0;
	i = 0;
	while (i < philo->args->nb_philos)
	{
		pthread_mutex_lock(philo->eat_mutex);
		if (philo[i].nb_meals == philo->args->nb_meals)
			all_ate++;
		pthread_mutex_unlock(philo->eat_mutex);
		i++;
	}
	if (all_ate == philo->args->nb_philos)
	{
		set_dead(philo);
	}
}

void	*checker_routine(void *arg)
{
	t_philo		*philo;
	// int			i;
	// u_int64_t	time;

	philo = (t_philo *)arg;
	while (not_dead(philo) == 0)
	{
		check_all_died(philo);
		check_all_ate(philo);
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
