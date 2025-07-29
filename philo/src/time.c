/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:51:25 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/29 21:34:19 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

unsigned int	get_current_time(void)
{
	struct timeval	tv;
	unsigned int	seconds_ms;
	unsigned int	microseconds_ms;

	if (gettimeofday(&tv, NULL))
		return (put_str_fd(STDERR, ERR_TIME), 0);
	seconds_ms = tv.tv_sec * 1000;
	microseconds_ms = tv.tv_usec / 1000;
	return (seconds_ms + microseconds_ms);
}

unsigned int	get_timestamp(unsigned int start_time)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - start_time;
	return (timestamp);
}

int	msleep(int miliseconds)
{
	int	microseconds;

	microseconds = miliseconds * 1000;
	if (usleep(microseconds))
		return (put_str_fd(STDERR, ERR_SLEEP), FAIL);
	return (SUCCES);
}

int	calculate_wait_time(t_philo *philosopher)
{
	int				time_since_meal;
	int				wait_time;
	unsigned int	start_time;

	start_time = philosopher->dinner->start;
	pthread_mutex_lock(&philosopher->meal_mutex);
	time_since_meal = get_timestamp(start_time) - philosopher->starvation;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	wait_time = 10 - (time_since_meal * 8 / philosopher->dinner->dead);
	if (wait_time < 1)
		wait_time = 1;
	return (wait_time);
}
