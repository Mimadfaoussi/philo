/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:41:28 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/01 14:36:40 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_mutex(philo, "has taken a fork");
	if (philo->args->nb_philos == 1)
	{
		ft_usleep(philo->args->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_mutex(philo, "has taken a fork");
	philo->is_eating = 1;
	print_mutex(philo, "is eating");
	update_meal(philo);
	ft_usleep(philo->args->time_to_eat);
	philo->is_eating = 0;
	put_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	print_mutex(philo, "is sleeping");
	ft_usleep(philo->args->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_mutex(philo, "is thinking");
}
