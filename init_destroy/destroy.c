/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:27:18 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/01 16:57:22 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	destroy_all(pthread_mutex_t *forks, t_data *data)
{
	destroy_forks(forks, data);
	destroy_data(data);
}

void	destroy_forks(pthread_mutex_t *forks, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos->args->nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	destroy_data(t_data *data)
{
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}
