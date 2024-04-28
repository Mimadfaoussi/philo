/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:47:38 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/04/28 12:34:11 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// struct timeval {
//     time_t      tv_sec;     // seconds
//     suseconds_t tv_usec;    // microseconds
// };

// int	gettimeofday(struct timeval *tv, struct timezone *tz);

// 1 sec = 1 000 milliseconds 
// 1 sec = 1 000 000 microseconds 

u_int64_t	get_precise_time(void)
{
	struct timeval	current_time;
	u_int64_t		time;

	if (gettimeofday(&current_time, NULL) != 0)
		return (0);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

void	ft_usleep(u_int64_t	time_to_wait)
{
	u_int64_t	start_time;

	start_time = get_precise_time();
	while ((get_precise_time() - start_time) < time_to_wait)
	{
		usleep(300);
	}
}

// int	main(void)
// {
// 	u_int64_t	start_time;
// 	u_int64_t	time_now;
// 	u_int64_t	time;

// 	start_time = get_precise_time();
// 	ft_usleep(10000);
// 	time_now = get_precise_time();
// 	time = time_now - start_time;
// 	printf("time in is : %llu ms\n",time);
// 	return (0);
// }