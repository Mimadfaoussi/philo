/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:55:38 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/01 14:39:30 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_mutex(t_philo *philo, char *str)
{
	u_int64_t	time;

	if (not_dead(philo) == 0)
	{
		time = get_precise_time() - philo->start_time;
		pthread_mutex_lock(philo->print_mutex);
		printf("%lu %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_mutex);
	philo->nb_meals++;
	philo->last_meal = get_precise_time();
	pthread_mutex_unlock(philo->eat_mutex);
}

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_meal = get_precise_time();
	pthread_mutex_unlock(philo->eat_mutex);
}

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	*(philo->is_dead) = 1;
	pthread_mutex_unlock(philo->dead_mutex);
}
