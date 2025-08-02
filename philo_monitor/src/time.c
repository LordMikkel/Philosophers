/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:51:25 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/29 23:56:10 by migarrid         ###   ########.fr       */
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
	int				urgency_factor;

	start_time = philosopher->dinner->start;
	pthread_mutex_lock(&philosopher->meal_mutex);
	time_since_meal = get_timestamp(start_time) - philosopher->starvation;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	urgency_factor = (time_since_meal * 100) / philosopher->dinner->dead;
	if (urgency_factor > 80)
		wait_time = 1;
	else if (urgency_factor > 60)
		wait_time = 2;
	else if (urgency_factor > 40)
		wait_time = 5;
	else if (urgency_factor > 20)
		wait_time = 8;
	else
		wait_time = 10;
	return (wait_time);
}
