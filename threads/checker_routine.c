/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:41:28 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/01 14:46:56 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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

void	check_all_died(t_philo *philo)
{
	int			i;
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

	philo = (t_philo *)arg;
	while (not_dead(philo) == 0)
	{
		check_all_died(philo);
		check_all_ate(philo);
	}
	return (NULL);
}
