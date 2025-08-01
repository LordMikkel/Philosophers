/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 04:10:02 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/01 15:33:50 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	if (philosopher->dinner->total == 1)
	{
		one_philosopher(philosopher);
		return (DEATH);
	}
	if (philosopher->id % 2 == 0)
		msleep(philosopher->dinner->eat / 2);
	while (!safe_read_end(philosopher->dinner))
	{
		thinks(philosopher);
		take_forks(philosopher);
		eats(philosopher);
		drop_forks(philosopher);
		if (has_eaten_enough(philosopher))
			break ;
		sleeps(philosopher);
	}
	return (SIMULATION_ENDED);
}

void	one_philosopher(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->fork_mutex);
	safe_print(philosopher, TAKE_FORK);
	msleep(philosopher->dinner->dead);
	pthread_mutex_unlock(&philosopher->fork_mutex);
}

int	has_eaten_enough(t_philo *philosopher)
{
	int	eaten;

	pthread_mutex_lock(&philosopher->meal_mutex);
	eaten = philosopher->meals;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	if (philosopher->dinner->meals > 0 && eaten >= philosopher->dinner->meals)
		return (SATISFYED);
	return (HUNGRY);
}

int	safe_read_end(t_dinner *dinner)
{
	int	end;

	pthread_mutex_lock(&dinner->end_mutex);
	end = dinner->stop;
	pthread_mutex_unlock(&dinner->end_mutex);
	return (end);
}
