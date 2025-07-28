/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:48:45 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/28 22:03:13 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	start_simulation(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->total)
	{
		if (pthread_create(&dinner->philosophers[i].thread, NO_ATRIBUTE,
				philosopher_routine, &dinner->philosophers[i]))
			return (put_str_fd(STDERR, ERR_THREAD), 0);
		i++;
	}
	if (pthread_create(&dinner->monitor.thread, NO_ATRIBUTE,
		monitor_routine, &dinner->monitor))
		return (put_str_fd(STDERR, ERR_THREAD), 0);
	return (1);
}

void	*philosopher_routine(t_philo *philosopher)
{
	if (philosopher->dinner->total == 1)
	{
		safe_print(philosopher, TAKE_L_FORK);
		usleep(philosopher->dinner->dead);
		return (NULL);
	}
}

void	*monitor_routine(t_monitor *monitor)
{
}
