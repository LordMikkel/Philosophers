/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 04:07:17 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/29 04:41:19 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


void	*monitor_routine(void *arg)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)arg;
	// while(monitor->dinner->stop)
	// {
		// 	// i = 0;
		// 	// while (i < monitor->dinner->total)
		// 	// {
			// 	// }
			// 	// i++;
			// }
	return (NULL);
}

int	request_for_forks(t_monitor *monitor)
{
	int	left_fork;
	int	right_fork;

	left_fork = calculate_fork_id(monitor->dinner->philosophers->id,
			monitor->dinner->total, 0);
	right_fork = calculate_fork_id(monitor->dinner->philosophers->id,
			monitor->dinner->total, 1);
	while (!monitor->dinner->stop)
	{
		pthread_mutex_lock(&monitor->service_mutex);
		if (monitor->forks_available[left_fork] == FREE &&
			monitor->forks_available[right_fork] == FREE)
		{
			monitor->forks_available[left_fork] = TAKEN;
			monitor->forks_available[left_fork] = TAKEN;
			pthread_mutex_unlock(&monitor->service_mutex);
			return (1);
		}
		pthread_mutex_unlock(&monitor->service_mutex);
	}
	return (0);
}

int		calculate_fork_id(int philo_id, int total_philo, int is_right_fork)
{
	if (is_right_fork)
		return(philo_id % total_philo);
	return ((philo_id - 1) % total_philo);
}

int	all_philosophers_are_satisfied(t_dinner *dinner)
{
}

int is_philosopher_dead(t_philo *philosopher)
{
}
