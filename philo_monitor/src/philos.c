/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 04:10:02 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/02 16:51:52 by migarrid         ###   ########.fr       */
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
		if (!request_for_forks(&philosopher->dinner->monitor, philosopher))
			return (SIMULATION_ENDED);
		eats(philosopher);
		if (has_eaten_enough(philosopher))
			break ;
		sleeps(philosopher);
		thinks(philosopher);
	}
	return (SIMULATION_ENDED);
}

void	one_philosopher(t_philo *philosopher)
{
	safe_print(philosopher, TAKE_L_FORK);
	msleep(philosopher->dinner->dead);
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
