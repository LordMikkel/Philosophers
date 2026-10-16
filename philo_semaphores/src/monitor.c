/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 04:07:17 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/04 19:18:29 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*monitor_routine(void *arg)
{
	t_philo		*philosopher;

	philosopher = (t_philo *)arg;
	while (!safe_read_end(philosopher->dinner))
	{
		if (is_philosopher_dead(philosopher))
		{
			death(philosopher);
			exit(EXIT_FAILURE);
		}
		if (has_eaten_enough(philosopher))
			break ;
		msleep(5);
	}
	return (SIMULATION_ENDED);
}

int	is_philosopher_dead(t_philo *philosopher)
{
	int	current_time;
	int	time_since_meal;

	current_time = get_timestamp(philosopher->dinner->start);
	sem_wait(philosopher->monitor->death);
	time_since_meal = current_time - philosopher->starvation;
	sem_post(philosopher->monitor->death);
	if (time_since_meal >= philosopher->dinner->dead)
		return (TRUE);
	return (FALSE);
}

void	kill_all_philosophers(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->total)
	{
		if (dinner->philosophers[i].pid > 0)
			kill(dinner->philosophers[i].pid, SIGTERM);
		i++;
	}
}
