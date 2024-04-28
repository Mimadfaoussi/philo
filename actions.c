/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:55:38 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/04/28 17:25:42 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_mutex(t_philo *philo, char *str)
{
	u_int64_t	time;

	if (not_dead(philo) == 0)
	{
		time = get_precise_time() - philo->start_time;
		pthread_mutex_lock(philo->print_mutex);
		printf("%llu philo %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_mutex(philo, "has taken left fork");
	if (philo->args->nb_philos == 1)
	{
		ft_usleep(philo->args->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_mutex(philo, "has taken right fork");
	philo->is_eating = 1;
	philo->nb_meals++;// still need to fix if it checks that if time is over but he is eating
	ft_usleep(philo->args->time_to_eat);
	philo->last_meal = get_precise_time();
	print_mutex(philo, "is eating");
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

