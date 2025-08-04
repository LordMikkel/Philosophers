/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 04:10:02 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/04 19:19:23 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	philosopher_routine(t_philo *philosopher)
{
	pthread_create(&philosopher->monitor->threads[philosopher->id - 1], NULL,
		monitor_routine, philosopher);
	pthread_detach(philosopher->monitor->threads[philosopher->id - 1]);
	if (philosopher->dinner->total == 1)
	{
		one_philosopher(philosopher);
		exit(RIP);
	}
	if (philosopher->id % 2 == 0)
		msleep(philosopher->dinner->eat / 2);
	while (!safe_read_end(philosopher->dinner))
	{
		take_forks(philosopher);
		eats(philosopher);
		drop_forks(philosopher);
		if (has_eaten_enough(philosopher))
			exit(FINISH);
		sleeps(philosopher);
		thinks(philosopher);
	}
	return (SIMULATION_ENDED);
}

void	one_philosopher(t_philo *philosopher)
{
	sem_wait(philosopher->monitor->forks);
	safe_print(philosopher, TAKE_FORK);
	msleep(philosopher->dinner->dead);
	sem_post(philosopher->monitor->forks);
}

int	has_eaten_enough(t_philo *philosopher)
{
	int	eaten;
	int	meals;

	meals = philosopher->dinner->meals;
	if (meals < 1)
		return (HUNGRY);
	sem_wait(philosopher->monitor->meals);
	eaten = philosopher->meals;
	sem_post(philosopher->monitor->meals);
	if (eaten >= meals)
		return (SATISFYED);
	return (HUNGRY);
}

int	safe_read_end(t_dinner *dinner)
{
	int	end;

	sem_wait(dinner->monitor.end);
	end = dinner->stop;
	sem_post(dinner->monitor.end);
	return (end);
}
