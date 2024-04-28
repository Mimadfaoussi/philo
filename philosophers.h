/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:07:06 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/04/28 13:04:23 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>

# define MAX_PHILOS 200

/** HELPER  functions */

int			ft_atoi(const char *str);

/*** checking input ***/

int			check_input(int argc, char **argv);

typedef struct s_args
{
	int						nb_philos;
	u_int64_t				time_to_die;
	u_int64_t				time_to_eat;
	u_int64_t				time_to_sleep;
	int						nb_meals;
}				t_args;

typedef struct s_philo
{
	int						id;
	pthread_t				thread;
	int						is_eating;
	int						nb_meals;
	int						is_dead;
	u_int64_t				start_time;
	u_int64_t				last_meal;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*dead_mutex;
	pthread_mutex_t			*print_mutex;
	t_args					*args;
}				t_philo;

typedef struct s_data
{
	int						dead;
	pthread_mutex_t			dead_mutex;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			*forks;
	t_philo					*philos;

}				t_data;

#endif